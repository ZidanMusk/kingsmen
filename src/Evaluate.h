#ifndef KINGSMEN_EVALUATE_H
#define KINGSMEN_EVALUATE_H

#include "Board.cpp"

class Evaluate {

    Board *_board;

    const int doubledPenaltyOpening[8];

    const int doubledPenaltyEnding[8];

    ull files[] = {
        0x0101010101010101,
                0x0202020202020202,
                0x0404040404040404,
                0x0808080808080808,
                0x1010101010101010,
                0x2020202020202020,
                0x4040404040404040,
                0x8080808080808080
    };

    ull ranks[] = {
        0x00000000000000FF,
                0x000000000000FF00,
                0x0000000000FF0000,
                0x00000000FF000000,
                0x000000FF00000000,
                0x0000FF0000000000,
                0x00FF000000000000,
                0xFF00000000000000
    };


public:
    explicit Evaluate(Board *b);

    int pawnStructureEval(int color);   //0 for white, 1 for black
    int kingSafty(int blackKingSafety, int whiteKingSafty); // arguments are calculated in mobility


    /// @brief Evaluates a given position.
    /// @return The heuristic score given to the position.
    int evaluate();
};

#endif //KINGSMEN_EVALUATE_H
