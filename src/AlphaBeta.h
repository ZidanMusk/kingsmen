//
// Created by zidan on 11/7/17.
//

#ifndef KINGSMEN_ALPHABETA_H
#define KINGSMEN_ALPHABETA_H
#include "Search.h"

class AlphaBeta : public Search{
public:
    AlphaBeta(ll maxDepth,Board* board,Evaluate* evaluate,int timeL):Search(maxDepth,board,evaluate,timeL) {}
    void getPvPath(ll root);

private:
    unordered_map <ll,ll> MoveTable;
    ll cntr=0;
    ll OpenedStates=0;
    ll alphaBetaSearch(ll alpha, ll beta, ll depth, bool isMax);
    void _IterativeDeepening(ll MaxDepth);
};
#endif //KINGSMEN_ALPHABETA_H
