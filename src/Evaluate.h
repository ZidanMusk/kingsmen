#ifndef KINGSMEN_EVALUATE_H
#define KINGSMEN_EVALUATE_H

#include "Board.cpp"

class Evaluate {

    Board *_board;

public:
    Evaluate(Board *b);

    int pawnStructureEval(int color);   //0 for white, 1 for black
    int kingSafty(int blackKingSafety, int whiteKingSafty); // arguments are calculated in mobility
};

#endif //KINGSMEN_EVALUATE_H
