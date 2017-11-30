#ifndef MTD_F_MTDF_H
#define MTD_F_MTDF_H

#include "Search.h"

class MTDF : public Search {
public:
    ll OpenedStates=0;
    ll EvalStates=0;
    bool doNull;
    bool useTrans;
    MTDF(ll maxDepth,Board* board,Evaluate* evaluate, bool nulling,bool trans):Search(maxDepth,board,evaluate) {this->doNull = nulling;this->useTrans=trans;}

private:
    unordered_map<ll,Node>_MTDfTable;
    void _IterativeDeepening(ll MaxDepth);
    ll _MTDF(ll f, ll d);
    ll _AlphaBetaWithMemory(ll alpha, ll beta,ll d,bool IsMax,ll MaxDepth,bool DoNull);
    void _UpdateNode(ll state_id,ll g ,ll alpha, ll beta);
    vector<int> _GetSortedPossibleMoves(ll state_id,ll IsMax);
};


#endif //MTD_F_MTDF_H
