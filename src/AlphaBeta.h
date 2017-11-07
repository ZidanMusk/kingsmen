//
// Created by zidan on 11/7/17.
//

#ifndef KINGSMEN_ALPHABETA_H
#define KINGSMEN_ALPHABETA_H

#include "Search.h"

class AlphaBeta : public Search{
public:
    AlphaBeta(int maxDepth):Search(maxDepth) {}

private:
    unordered_map <int,int> MoveTable;
    int cntr=0;
    int alphaBetaSearch(int stateID, int alpha, int beta, int depth, bool isMax);
    pair<int,int> _IterativeDeepening(int root_id,int MaxDepth);

};


#endif //KINGSMEN_ALPHABETA_H
