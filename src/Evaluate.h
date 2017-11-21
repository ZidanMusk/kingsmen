#ifndef KINGSMEN_EVALUATE_H
#define KINGSMEN_EVALUATE_H

#include "Board.cpp"

class Evaluate {

    Board *_board;

    const int doubledPenaltyOpening[8];

    const int doubledPenaltyEnding[8];

public:
    explicit Evaluate(Board *b);

    int pawnStructureEval(int color);   //0 for white, 1 for black
    int kingSafty(int blackKingSafety, int whiteKingSafty); // arguments are calculated in mobility

    /// @brief Evaluates a given position.
    /// @return The heuristic score given to the position.
    int evaluate();

    int mobilityEval(std::array<int, 2>& kingSafetyScore, int phase);
};

#endif //KINGSMEN_EVALUATE_H
