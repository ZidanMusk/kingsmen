#include "Evaluate.h"

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