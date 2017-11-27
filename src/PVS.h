#ifndef CHESS_SEARCH_PVS_H
#define CHESS_SEARCH_PVS_H

#include "Search.h"

class PVS : public Search{
public:
    ll OpenedStates=0;
    bool doNull;
    PVS(ll maxDepth,bool nulling):Search(maxDepth) {this->doNull = nulling;}
    void getPvPath(ll root);
private:
    unordered_map <ll,ll> PvTable;
    unordered_map <ll,ll> VisitedStates;
    ll cntr=0;
    //set<ll>visitedStates;
    ll pvsSearch(ll stateID, ll alpha, ll beta, ll depth, bool isMax);
    void _IterativeDeepening(ll root_id,ll MaxDepth);

};


#endif //CHESS_SEARCH_PVS_H
