#include "Evaluate.h"
#include <bitset>
template<class T>
T clamp(T value, T lowerBound, T upperBound) {
    return std::max(lowerBound, std::min(value, upperBound));
}

int bishopPairBonusOpening = 42;
int bishopPairBonusEnding = 52;
int sideToMoveBonus = 1;


Evaluate::Evaluate(Board *b) {
    _board = b;
    pht.setSize(4);
}

inline int Evaluate::interpolateScore(int scoreOp, int scoreEd, int phase) {
    return ((scoreOp * (64 - phase)) + (scoreEd * phase)) >> 6;
}

int Evaluate::pawnStructure(int phase) {
    auto scoreOp = 0, scoreEd = 0;

    if (pht.probe(_board->ZPawns(), scoreOp, scoreEd)) {
        return interpolateScore(scoreOp, scoreEd, phase);
    }

    for (int c = 0; c <= 1; ++c) {
        const auto ownPawns = c == 1 ? _board->blackPawns : _board->whitePawns;
        const auto opponentPawns = c == 1 ? _board->whitePawns : _board->blackPawns;
        auto tempPawns = ownPawns;
        auto scoreOpForColor = 0, scoreEdForColor = 0;

        while (tempPawns) {
            const auto from = _board->popLsb(tempPawns);
            const auto pawnFile = (from % 8);
            const auto pawnRank = (c ? 7 - (from / 8) : (from / 8));

            const auto passed = !(opponentPawns & Passed[c][from]);
            const auto doubled = (ownPawns & (c ? Rays[1][from] : Rays[6][from])) != 0;
            const auto isolated = !(ownPawns & Isolated[from]);
            const auto backward = !(ownPawns & Backward[c][from])
                                  && _board->getPieceAt(from + 8 - 16 * c) != 'P'
                                  && _board->getPieceAt(from + 8 - 16 * c) != 'p'
                                  && (PawnAttacks[c][from + 8 - 16 * c] & opponentPawns);
            //cout << passed << ' ' << doubled << ' ' << isolated << ' ' << backward << endl;
            if (passed) {
                scoreOpForColor += passedBonusOpening[pawnRank];
                scoreEdForColor += passedBonusEnding[pawnRank];
            }

            if (doubled) {
                scoreOpForColor -= doubledPenaltyOpening[pawnFile];
                scoreEdForColor -= doubledPenaltyEnding[pawnFile];
            }

            if (isolated) {
                scoreOpForColor -= isolatedPenaltyOpening[pawnFile];
                scoreEdForColor -= isolatedPenaltyEnding[pawnFile];
            }

            if (backward) {
                scoreOpForColor -= backwardPenaltyOpening[pawnFile];
                scoreEdForColor -= backwardPenaltyEnding[pawnFile];
            }
        }

        scoreOp += (c ? -scoreOpForColor : scoreOpForColor);
        scoreEd += (c ? -scoreEdForColor : scoreEdForColor);
        //cout << scoreOpForColor << ' ' << scoreEdForColor << endl;
    }

    pht.save(_board->ZPawns(), scoreOp, scoreEd);

    return interpolateScore(scoreOp, scoreEd, phase);
}

int Evaluate::kingSafty(int blackKingSafety, int whiteKingSafty, int phase) {
    //cout<<blackKingSafety<<" BLACK"<<endl;
    ////cout<<whiteKingSafty<<" WHITE"<<endl;
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

    auto scoreOp = 0, scoreEd = 0;

    for (int c = 0; c <= 1; ++c) {

        // king safety array access with king color and place on board

        const auto opponentKingZone = _board->kingSafetyZone[_board->getLsb(
                _board->getBitBoard(!c, 5))][!c]; // 5 -> king
        auto scoreOpForColor = 0, scoreEdForColor = 0;
        auto attackUnits = 0;

        auto tempPiece = _board->getBitBoard(c, 1); // 1 -> knight
        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            const ull tempMove = _board->knightAttacks(from, c);
            const auto count = _board->popCnt(tempMove);
            scoreOpForColor += mobilityOpening[1][count];
            scoreEdForColor += mobilityEnding[1][count];
            attackUnits += attackWeight[1] * _board->popCnt(tempMove & opponentKingZone);
        }

        tempPiece = _board->getBitBoard(c, 2); // 2 -> Bishop
        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            ull tempMove = _board->bishopAttacks(from, c, 0); // default
            const auto count = _board->popCnt(tempMove);
            scoreOpForColor += mobilityOpening[2][count];
            scoreEdForColor += mobilityEnding[2][count];
            tempMove = _board->bishopAttacks(from, c, 1); // turn off queens
            attackUnits += attackWeight[2] * _board->popCnt(tempMove & opponentKingZone);
        }

        tempPiece = _board->getBitBoard(c, 3); // 3 -> rook
        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            ull tempMove = _board->rookAttacks(from, c, 0);
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
        }

        tempPiece = _board->getBitBoard(c, 4); // 4 -> Queen
        while (tempPiece) {
            const auto from = _board->popLsb(tempPiece);
            const ull tempMove = _board->queenAttacks(from, c, 0);
            const auto count = _board->popCnt(tempMove);
            scoreOpForColor += mobilityOpening[4][count];
            scoreEdForColor += mobilityEnding[4][count];
            attackUnits += attackWeight[4] * _board->popCnt(tempMove & opponentKingZone);
        }

        kingSafetyScore[c] = attackUnits;
        scoreOp += (c ? -scoreOpForColor : scoreOpForColor);
        scoreEd += (c ? -scoreEdForColor : scoreEdForColor);
    }
    return interpolateScore(scoreOp, scoreEd, phase);
}

int Evaluate::evaluate() {

    // IF DRAW RETURN 0
//    if () {
//        return 0;
//    }
    clock_t tStart = clock();

    std::array<int, 2> kingSafetyScore;
    auto phase = clamp(static_cast<int>(_board->getGamePhase()), 0, 64);

    auto score = mobilityEval(kingSafetyScore, phase);
    //cout << "mobility " << score << endl;
    score += pawnStructure(phase);
    //cout << "pawn structure " << score << endl;
    score += kingSafty(kingSafetyScore[1], kingSafetyScore[0], phase);
    //cout << "king safety " << score << endl;
    score += interpolateScore(_board->getPstScoreOp(), _board->getPstScoreEd(), phase);

    // Bishop pair bonus.
    for (Color c = Color::White; c <= Color::Black; ++c) {
        if (_board->getPieceCount(c, Piece::Bishop) == 2) {
            const auto bishopPairBonus = interpolateScore(bishopPairBonusOpening, bishopPairBonusEnding, phase);
            score += (c ? -bishopPairBonus : bishopPairBonus);
        }
    }
    //cout<< "pst " << score<<endl;
    score += (_board->whiteToMove ? sideToMoveBonus : -sideToMoveBonus);
//    //cout<<score<<endl;
    xx += (clock() - tStart);
    xxx++;
    return score;
}
