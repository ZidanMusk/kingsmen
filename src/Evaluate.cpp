#include "Evaluate.h"

template <class T>
T clamp(T value, T lowerBound, T upperBound)
{
    return std::max(lowerBound, std::min(value, upperBound));
}

const int bishopPairBonusOpening = 42;
const int bishopPairBonusEnding = 52;
const int sideToMoveBonus = 1;


Evaluate::Evaluate(Board *b)
{
    _board = b;
    pht.setSize(4);
}

int Evaluate::interpolateScore(int scoreOp, int scoreEd, int phase)
{
    return ((scoreOp * (64 - phase)) + (scoreEd * phase)) / 64;
}

int Evaluate::pawnStructure(int phase) {
    auto scoreOp = 0, scoreEd = 0;

    if (pht.probe(_board->ZPawns(), scoreOp, scoreEd))
    {
        return interpolateScore(scoreOp, scoreEd, phase);
    }

    for (int c = 0; c <= 1; ++c)
    {
        const auto ownPawns = c? _board->blackPawns : _board->whitePawns;
        const auto opponentPawns = c? _board->whitePawns : _board->blackPawns;
        auto tempPawns = ownPawns;
        auto scoreOpForColor = 0, scoreEdForColor = 0;

        while (tempPawns)
        {
            const auto from = _board->popLsb(tempPawns);
            const auto pawnFile = (from%8);
            const auto pawnRank = (c ? 7 - (from/8) : (from/8));

            const auto passed = !(opponentPawns & Passed[c][from]);
            const auto doubled = (ownPawns & (c ? Rays[1][from] : Rays[6][from])) != 0;
            const auto isolated = !(ownPawns & Isolated[from]);
            const auto backward = !(ownPawns & Backward[c][from])
                                  && _board->getPieceAt(from + 8 - 16 * c) != 'P'
                                  && _board->getPieceAt(from + 8 - 16 * c) != 'p'
                                  && (PawnAttacks[c][from + 8 - 16 * c] & opponentPawns);

            if (passed)
            {
                scoreOpForColor += passedBonusOpening[pawnRank];
                scoreEdForColor += passedBonusEnding[pawnRank];
            }

            if (doubled)
            {
                scoreOpForColor -= doubledPenaltyOpening[pawnFile];
                scoreEdForColor -= doubledPenaltyEnding[pawnFile];
            }

            if (isolated)
            {
                scoreOpForColor -= isolatedPenaltyOpening[pawnFile];
                scoreEdForColor -= isolatedPenaltyEnding[pawnFile];
            }

            if (backward)
            {
                scoreOpForColor -= backwardPenaltyOpening[pawnFile];
                scoreEdForColor -= backwardPenaltyEnding[pawnFile];
            }
        }

        scoreOp += (c? -scoreOpForColor : scoreOpForColor);
        scoreEd += (c? -scoreEdForColor : scoreEdForColor);
    }

    pht.save(_board->ZPawns(), scoreOp, scoreEd);

    return interpolateScore(scoreOp, scoreEd, phase);
}

int Evaluate::kingSafty(int blackKingSafety, int whiteKingSafty, int phase) {
    //evaluate white pawn shelter
    int penalty = 0;
    int kingFile = min(1, max(6, _board->getColumn(log2(_board->whiteKing) + _board->EPS)));
    for (int i = kingFile - 1; i <= kingFile; i++) {
        ull whitePawnsOfFile = files[i] & _board->whitePawns;
        ull blackPawnsOfFile = files[i] & _board->blackPawns;
        penalty += (whitePawnsOfFile | blackPawnsOfFile) ? 0 : openFilePenalty[i];
        penalty += (!whitePawnsOfFile && blackPawnsOfFile) ? halfopenFilePenalty[i] : 0;
        penalty += blackPawnsOfFile ? pawnStormPenalty[7 -
                                                       (int) ((log2(_board->getLSB(blackPawnsOfFile)) + _board->EPS) /
                                                              8)] : 0;
    }
    int whitePawnShelterPenalty = penalty;

    //evaluate black pawn shelter
    penalty = 0;
    kingFile = min(1, max(6, _board->getColumn(log2(_board->blackKing) + _board->EPS)));
    for (int i = kingFile - 1; i <= kingFile; i++) {
        ull whitePawnsOfFile = files[i] & _board->whitePawns;
        ull blackPawnsOfFile = files[i] & _board->blackPawns;
        penalty += (whitePawnsOfFile | blackPawnsOfFile) ? 0 : openFilePenalty[i];
        penalty += (whitePawnsOfFile && !blackPawnsOfFile) ? halfopenFilePenalty[i] : 0;
        penalty += whitePawnsOfFile ? pawnStormPenalty[(int) ((log2(_board->getMSB(whitePawnsOfFile)) + _board->EPS) /
                                                              8)] : 0;
    }
    int blackPawnShelterPenalty = penalty;

    whiteKingSafty += whitePawnShelterPenalty;
    blackKingSafety += blackPawnShelterPenalty;
    whiteKingSafty = min(whiteKingSafty, 99);
    blackKingSafety = min(blackKingSafety, 99);

    int score = kingSafetyTable[whiteKingSafty] - kingSafetyTable[blackKingSafety];
    return ((score * (64 - phase)) / 64);

}

int Evaluate::mobilityEval(std::array<int, 2> &kingSafetyScore, int phase) {
//    const auto occupied = _board->getOccupiedSquares();
//    const auto occupied = pos.getOccupiedSquares();
    auto scoreOp = 0, scoreEd = 0;

    for (int c = 0; c <= 1; ++c) {

        // king safety array access with king color and place on board
        cout<<_board->getBitBoard(!c, 5)<<endl;
        cout<<_board->getLsb(_board->getBitBoard(!c, 5))<<endl;
        const auto opponentKingZone = _board->kingSafetyZone[!c][_board->getLsb(_board->getBitBoard(!c, 5))]; // 5 -> king
//        const auto targetBitboard = ~pos.getPieces(c);
//        const auto opponentKingZone = Bitboards::kingSafetyZone(!c, Bitboards::lsb(pos.getBitboard(!c, Piece::King)));
        auto scoreOpForColor = 0, scoreEdForColor = 0;
        auto attackUnits = 0;

        auto tempPiece = _board->getBitBoard(c, 1); // 1 -> knight
//        auto tempPiece = pos.getBitboard(c, Piece::Knight);

        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            const auto tempMove = _board->knightAttacks(from, c);
            const auto count = _board->popCnt(tempMove);
            scoreOpForColor += mobilityOpening[1][count];
            scoreEdForColor += mobilityEnding[1][count];
            attackUnits += attackWeight[1] * _board->popCnt(tempMove & opponentKingZone);

//            const auto from = Bitboards::popLsb(tempPiece);
//            const auto tempMove = Bitboards::knightAttacks(from) & targetBitboard;
//            const auto count = Bitboards::popcnt<hardwarePopcnt>(tempMove);
//            scoreOpForColor += mobilityOpening[Piece::Knight][count];
//            scoreEdForColor += mobilityEnding[Piece::Knight][count];
//            attackUnits += attackWeight[Piece::Knight] * Bitboards::popcnt<hardwarePopcnt>(tempMove & opponentKingZone);
        }

        tempPiece = _board->getBitBoard(c, 2); // 2 -> Bishop
//        tempPiece = pos.getBitboard(c, Piece::Bishop);
        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            auto tempMove = _board->bishopAttacks(from, c, 0); // default
            const auto count = _board->popCnt(tempMove);
            scoreOpForColor += mobilityOpening[2][count];
            scoreEdForColor += mobilityEnding[2][count];
            tempMove = _board->bishopAttacks(from, c, 1); // turn off queens
            attackUnits += attackWeight[2] * _board->popCnt(tempMove & opponentKingZone);

//            const auto from = Bitboards::popLsb(tempPiece);
//            auto tempMove = Bitboards::bishopAttacks(from, occupied) & targetBitboard;
//            const auto count = Bitboards::popcnt<hardwarePopcnt>(tempMove);
//            scoreOpForColor += mobilityOpening[Piece::Bishop][count];
//            scoreEdForColor += mobilityEnding[Piece::Bishop][count];
//            tempMove = Bitboards::bishopAttacks(from, occupied ^ pos.getBitboard(c, Piece::Queen)) & targetBitboard;
//            attackUnits += attackWeight[Piece::Bishop] * Bitboards::popcnt<hardwarePopcnt>(tempMove & opponentKingZone);
        }

        tempPiece = _board->getBitBoard(c, 3); // 3 -> rook
//        tempPiece = pos.getBitboard(c, Piece::Rook);
        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            auto tempMove = _board->rookAttacks(from, c, 0);
            const auto count = _board->popCnt(tempMove);
            scoreOpForColor += mobilityOpening[3][count];
            scoreEdForColor += mobilityEnding[3][count];
            tempMove = _board->rookAttacks(from, c, 1);
            attackUnits += attackWeight[3] * _board->popCnt(tempMove & opponentKingZone);

            if (!(files[_board->getColumn(from)] & _board->getBitBoard(c, 0))) { // 0 -> pawn
                if (!(files[_board->getColumn(from)] & _board->getBitBoard(!c, 0))) { // 0 -> pawn
                    scoreOpForColor += 26;
                } else {
                    scoreOpForColor += 13;
                }
            }
//            const auto from = Bitboards::popLsb(tempPiece);
//            auto tempMove = Bitboards::rookAttacks(from, occupied) & targetBitboard;
//            const auto count = Bitboards::popcnt<hardwarePopcnt>(tempMove);
//            scoreOpForColor += mobilityOpening[Piece::Rook][count];
//            scoreEdForColor += mobilityEnding[Piece::Rook][count];
//            tempMove = Bitboards::rookAttacks(from, occupied ^ pos.getBitboard(c, Piece::Queen) ^
//                                                    pos.getBitboard(c, Piece::Rook)) & targetBitboard;
//            attackUnits += attackWeight[Piece::Rook] * Bitboards::popcnt<hardwarePopcnt>(tempMove & opponentKingZone);
//
//            if (!(Bitboards::files[file(from)] & pos.getBitboard(c, Piece::Pawn))) {
//                if (!(Bitboards::files[file(from)] & pos.getBitboard(!c, Piece::Pawn))) {
//                    scoreOpForColor += 26;
//                } else {
//                    scoreOpForColor += 13;
//                }
//            }
        }

        tempPiece = _board->getBitBoard(c, 4); // 4 -> Queen
//        tempPiece = pos.getBitboard(c, Piece::Queen);
        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            const auto tempMove = _board->queenAttacks(from, c, 0);
            const auto count = _board->popCnt(tempMove);
            scoreOpForColor += mobilityOpening[4][count];
            scoreEdForColor += mobilityEnding[4][count];
            attackUnits += attackWeight[4] * _board->popCnt(tempMove & opponentKingZone);

//            const auto from = Bitboards::popLsb(tempPiece);
//            const auto tempMove = Bitboards::queenAttacks(from, occupied) & targetBitboard;
//            const auto count = Bitboards::popcnt<hardwarePopcnt>(tempMove);
//            scoreOpForColor += mobilityOpening[Piece::Queen][count];
//            scoreEdForColor += mobilityEnding[Piece::Queen][count];
//            attackUnits += attackWeight[Piece::Queen] * Bitboards::popcnt<hardwarePopcnt>(tempMove & opponentKingZone);
        }

        kingSafetyScore[c] = attackUnits;
        scoreOp += (c ? -scoreOpForColor : scoreOpForColor);
        scoreEd += (c ? -scoreEdForColor : scoreEdForColor);
    }
    cout << scoreOp << ' ' << scoreEd << ' ' << phase << endl;
    return interpolateScore(scoreOp, scoreEd, phase);
}

int Evaluate::getPstScore(int phase) {
    return interpolateScore(_board->getPstScoreOp(), _board->getPstScoreEd(), phase);
}

int Evaluate::evaluate() {

    // IF DRAW RETURN 0
//    if () {
//        return 0;
//    }

    std::array<int, 2>kingSafetyScore;
    const auto phase = clamp(static_cast<int>(_board->getGamePhase()), 0, 64);

    auto score = mobilityEval(kingSafetyScore, phase);
    cout<<score<<endl;
    score += pawnStructure(phase);
    cout<<score<<endl;
    score += kingSafty(kingSafetyScore[1], kingSafetyScore[0], phase);
    cout<<score<<endl;
    //score += getPstScore(phase);

    // Bishop pair bonus.
    for (Color c = Color::White; c <= Color::Black; ++c) {
        if (_board->getPieceCount(c, Piece::Bishop) == 2) {
            const auto bishopPairBonus = interpolateScore(bishopPairBonusOpening, bishopPairBonusEnding, phase);
            score += (c ? -bishopPairBonus : bishopPairBonus);
        }
    }
    cout<<score<<endl;
    score += (_board->whiteToMove ? sideToMoveBonus : -sideToMoveBonus);
    cout<<score<<endl;
    return score;
}
