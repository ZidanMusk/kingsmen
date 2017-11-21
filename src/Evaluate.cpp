#include "Evaluate.h"

const std::array<std::vector<int>, 6> mobilityOpening = {{
                                                                 {},
                                                                 {-1, 6, 12, 16, 17, 16, 16, 15, 18},
                                                                 {-12, -7, -2, 1, 6, 14, 17, 22, 19, 23, 21, 34, 34, 29},
                                                                 {-15, -12, -5, -3, -4, -1, 0, 6, 3, 1, 4, 4, 7, 14, 20},
                                                                 {35, -5, -8, -8, -6, -4, -6, -3, 1, -1, 5, 7, 6, 6, 8, 4, 2, 6, 4, 7, 17, 21, 30, 24, 41, 41, 36, 34},
                                                                 {}
                                                         }};

const std::array<std::vector<int>, 6> mobilityEnding = {{
                                                                {},
                                                                {-30, 1, 4, 11, 16, 25, 23, 23, 19},
                                                                {-22, -32, -19, -6, 5, 20, 29, 33, 42, 40, 36, 38, 28, 13},
                                                                {-12, -12, -8, -5, 7, 16, 20, 22, 31, 42, 43, 47, 47, 47, 37},
                                                                {-2, 5, -2, -23, -28, -29, -14, -12, -10, -3, -5, -1, 6, 14, 17, 22, 36, 34, 43, 37, 39, 33, 36, 22, 12, -4, 38, 26},
                                                                {}
                                                        }};
const std::array<int, 6> attackWeight = {
        0, 2, 2, 3, 5, 0
};

Evaluate::Evaluate(Board *b) : doubledPenaltyOpening({
                                                             36, 9, 2, 23, 18, 20, 0, 26
                                                     }), doubledPenaltyEnding({
                                                                                      46, 25, 31, 24, 21, 19, 29, 44
                                                                              }) {
    _board = b;
}

int Evaluate::pawnStructureEval(int color) {
    ull tmpPawns = color ? _board->blackPawns : _board->whitePawns;

    while (tmpPawns) {
        int loc = _board->getLSB(tmpPawns);
    }
}

int Evaluate::kingSafty(int blackKingSafety, int whiteKingSafty) {

    ull openFilePenalty[] = {6, 5, 4, 4, 4, 4, 5, 6},
            halfopenFilePenalty[] = {5, 4, 3, 3, 3, 3, 4, 5},
            pawnStormPenalty[] = {0, 0, 0, 1, 2, 3, 0, 0},
            piecePhase[] = {0, 3, 3, 5, 10, 0},
            files[] = {
            0x0101010101010101,
            0x0202020202020202,
            0x0404040404040404,
            0x0808080808080808,
            0x1010101010101010,
            0x2020202020202020,
            0x4040404040404040,
            0x8080808080808080
    },
            ranks[] = {
            0x00000000000000FF,
            0x000000000000FF00,
            0x0000000000FF0000,
            0x00000000FF000000,
            0x000000FF00000000,
            0x0000FF0000000000,
            0x00FF000000000000,
            0xFF00000000000000
    },
            kingSafetyTable[] = {
            21, 7, 11, 7, 7, 9, 5, 7, 10, 14, 15, 20, 19, 20, 25, 22, 28, 40, 45, 47, 46, 60, 56, 82, 86, 102, 98,
            109, 107, 117, 125, 132, 159, 168, 181, 188, 211, 213, 234, 216, 265, 276, 288, 272, 308, 339, 351, 355,
            374, 354, 370, 412, 420, 481, 439, 457, 478, 478, 441, 509, 494, 431, 517, 569, 562, 499, 500, 531, 523,
            500, 500, 500, 522, 517, 500, 500, 500, 508, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
            500, 500, 500, 500, 500, 500, 500, 500, 500, 500
    };
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
    int phase = piecePhase[_board->pawnTypeNum()] * 16 + piecePhase[_board->knightTypeNum()] * 4
                + piecePhase[_board->bishopTypeNum()] * 4 + piecePhase[_board->rookTypeNum()] * 4
                + piecePhase[_board->queenTypeNum()] * 2;
    phase -=
            (__builtin_popcountll(_board->whiteKnights) + __builtin_popcountll(_board->blackKnights)) *
            piecePhase[_board->knightTypeNum()];
    phase -=
            (__builtin_popcountll(_board->whiteBishops) + __builtin_popcountll(_board->blackBishops)) *
            piecePhase[_board->bishopTypeNum()];
    phase -= (__builtin_popcountll(_board->whiteRooks) + __builtin_popcountll(_board->blackRooks)) *
             piecePhase[_board->rookTypeNum()];
    phase -= (__builtin_popcountll(_board->whiteQueens) + __builtin_popcountll(_board->blackQueens)) *
             piecePhase[_board->queenTypeNum()];

    whiteKingSafty += whitePawnShelterPenalty;
    blackKingSafety += blackPawnShelterPenalty;
    whiteKingSafty = min(whiteKingSafty, 99);
    blackKingSafety = min(blackKingSafety, 99);

    int score = kingSafetyTable[whiteKingSafty] - kingSafetyTable[blackKingSafety];
    return ((score * (64 - phase)) / 64);

}

int interpolateScore(int scoreOp, int scoreEd, int phase) {
    return ((scoreOp * (64 - phase)) + (scoreEd * phase)) / 64;
}

template<bool hardwarePopcnt>
int Evaluation::evaluate() {
    // IF DRAW RETURN 0
    if (mEndgameModule.drawnEndgame(pos.getMaterialHashKey())) {
        return 0;
    }

    std::array<int, 2> kingSafetyScore;
    const auto phase = clamp(static_cast<int>(pos.getGamePhase()), 0,
                             64); // The phase can be negative in some weird cases, guard against that.

    auto score = mobilityEval<hardwarePopcnt>(pos, kingSafetyScore, phase);
    score += pawnStructureEval(pos, phase);
    score += kingSafetyEval(pos, phase, kingSafetyScore);
    score += interpolateScore(pos.getPstScoreOp(), pos.getPstScoreEd(), phase);

    // Bishop pair bonus.
    for (Color c = Color::White; c <= Color::Black; ++c) {
        if (pos.getPieceCount(c, Piece::Bishop) == 2) {
            const auto bishopPairBonus = interpolateScore(bishopPairBonusOpening, bishopPairBonusEnding, phase);
            score += (c ? -bishopPairBonus : bishopPairBonus);
        }
    }

    score += (pos.getSideToMove() ? -sideToMoveBonus : sideToMoveBonus);

    return (pos.getSideToMove() ? -score : score);
}

int Evaluate::mobilityEval(std::array<int, 2> &kingSafetyScore, int phase) {
//    const auto occupied = _board->getOccupiedSquares();
//    const auto occupied = pos.getOccupiedSquares();
    auto scoreOp = 0, scoreEd = 0;

    for (int c = 0; c <= 1; ++c) {

        // king safety array access with king color and place on board
        const auto opponentKingZone = _board->kingSafetyZone[!c][_board->getLSB(
                _board->getBitBoard(!c, 5))]; // 5 -> king
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

    return interpolateScore(scoreOp, scoreEd, phase);
}


