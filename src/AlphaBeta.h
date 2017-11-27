//
// Created by zidan on 11/7/17.
//

#ifndef KINGSMEN_ALPHABETA_H
#define KINGSMEN_ALPHABETA_H
#include "Search.h"

class AlphaBeta : public Search{
public:
    AlphaBeta(ll maxDepth):Search(maxDepth) {}
    void getPvPath(ll root);

private:
    unordered_map <ll,ll> MoveTable;
    ll cntr=0;
    ll OpenedStates=0;
    ll alphaBetaSearch(ll stateID, ll alpha, ll beta, ll depth, bool isMax);
    void _IterativeDeepening(ll root_id,ll MaxDepth);

};


#endif //KINGSMEN_ALPHABETA_H
