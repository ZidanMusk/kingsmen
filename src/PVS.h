#ifndef CHESS_SEARCH_PVS_H
#define CHESS_SEARCH_PVS_H

#include "Search.h"

class PVS : public Search{
public:
    ll OpenedStates=0;
    bool doNull;
    PVS(ll maxDepth,Board* board,Evaluate* evaluate,bool nulling,int time):Search(maxDepth, board,evaluate,time) {this->doNull = nulling;}
    void getPvPath(ll root);
private:
    unordered_map <ll,int> PvTable;
    unordered_map <ll,ll> VisitedStates;
    ll cntr=0;
    ll pvsSearch(ll alpha, ll beta, ll depth, bool isMax, ll maxDepth);
    void _IterativeDeepening(ll MaxDepth);

};
#endif //CHESS_SEARCH_PVS_H
