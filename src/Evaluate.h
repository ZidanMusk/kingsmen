#ifndef KINGSMEN_EVALUATE_H
#define KINGSMEN_EVALUATE_H

#include "Board.cpp"

class Evaluate {

    Board *_board;

    const int doubledPenaltyOpening[] = {
            36, 9, 2, 23, 18, 20, 0, 26
    };

    const int doubledPenaltyEnding[] = {
            46, 25, 31, 24, 21, 19, 29, 44
    };

public:
    Evaluate(Board *b);

    int pawnStructureEval(int color);   //0 for white, 1 for black
};

#endif //KINGSMEN_EVALUATE_H
