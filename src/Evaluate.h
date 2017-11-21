#ifndef KINGSMEN_EVALUATE_H
#define KINGSMEN_EVALUATE_H

#include "Board.cpp"



class Evaluate {

    Board *_board;

    const int doubledPenaltyOpening[8];

    const int doubledPenaltyEnding[8];

    ull files[8];
    ull ranks[8];

    // These two have to be annoyingly static, as we use them in position.cpp to incrementally update the PST eval.
    static std::array<std::array<short, 64>, 12> mPieceSquareTableOpening;
    static std::array<std::array<short, 64>, 12> mPieceSquareTableEnding;


public:
    explicit Evaluate(Board *b);

    /// @brief Evaluates a given position.
    /// @return The heuristic score given to the position.
    int evaluate();

    int pawnStructureEval(int color);   //0 for white, 1 for black
    int kingSafety(int blackKingSafety, int whiteKingSafty); // arguments are calculated in mobility

    int interpolateScore(int scoreOp, int scoreEd, int phase);

    int getPstScore();

    int mobilityEval(std::array<int, 2>& kingSafetyScore, int phase);

    inline short getPieceSquareTableOp(Piece p, Square sq) {
        return mPieceSquareTableOpening[p][sq];
    }

    inline short getPieceSquareTableEd(Piece p, Square sq) {
        return mPieceSquareTableEnding[p][sq];
    }

};

#endif //KINGSMEN_EVALUATE_H
