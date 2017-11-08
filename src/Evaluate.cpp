#include "Evaluate.h"

Evaluate::Evaluate(Board *b) {
    _board = b;
}

int Evaluate::pawnStructureEval(int color) {
    ull tmpPawns = color ? _board->blackPawns : _board->whitePawns;

    while (tmpPawns) {
        int loc = _board->getLSB(tmpPawns);
    }
}

