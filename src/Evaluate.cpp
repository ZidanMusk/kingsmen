#include "Evaluate.h"

Evaluate::Evaluate(Board *b) {
    _board = b;
}

int Evaluate::pawnStructureEval(int color) {

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
        penalty += blackPawnsOfFile ? pawnStormPenalty[7 - (int) ((log2(_board->getLSB(blackPawnsOfFile)) + _board->EPS) / 8)] : 0;
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
        penalty += whitePawnsOfFile ? pawnStormPenalty[(int) ((log2(_board->getMSB(whitePawnsOfFile)) + _board->EPS) / 8)] : 0;
    }
    int blackPawnShelterPenalty = penalty;
    int phase = piecePhase[_board->pawnTypeNum()] * 16 + piecePhase[_board->knightTypeNum()] * 4
                + piecePhase[_board->bishopTypeNum()] * 4 + piecePhase[_board->rookTypeNum()] * 4
                + piecePhase[_board->queenTypeNum()] * 2;
    phase -=
            (__builtin_popcountll(_board->whiteKnights) + __builtin_popcountll(_board->blackKnights)) * piecePhase[_board->knightTypeNum()];
    phase -=
            (__builtin_popcountll(_board->whiteBishops) + __builtin_popcountll(_board->blackBishops)) * piecePhase[_board->bishopTypeNum()];
    phase -= (__builtin_popcountll(_board->whiteRooks) + __builtin_popcountll(_board->blackRooks)) * piecePhase[_board->rookTypeNum()];
    phase -= (__builtin_popcountll(_board->whiteQueens) + __builtin_popcountll(_board->blackQueens)) * piecePhase[_board->queenTypeNum()];

    whiteKingSafty += whitePawnShelterPenalty;
    blackKingSafety += blackPawnShelterPenalty;
    whiteKingSafty = min(whiteKingSafty, 99);
    blackKingSafety = min(blackKingSafety, 99);

    int score = kingSafetyTable[whiteKingSafty] - kingSafetyTable[blackKingSafety];
    return ((score * (64 - phase)) / 64);

}