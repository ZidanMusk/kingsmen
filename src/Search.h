#ifndef CHESSSEARCH_SEARCH_H
#define CHESSSEARCH_SEARCH_H
#define oo  1e9
#define MAX_R 4
#define MIN_R 3
#define hashfEXACT   0
#define hashfALPHA   1
#define hashfBETA    2
#define valUNKNOWN -oo

#include "Evaluate.h"
#include "External/ExternBig.h"
#include <unordered_map>
#include <map>
#include <iostream>
#include <algorithm>
#include <set>
#include <time.h>
#include "cassert"
using namespace std;


struct Node
{
    ll value=-oo;
    ll lowerbound=-oo;
    ll upperbound=+oo;
};
struct TransitionEntry {
    ll Depth;
    ll HashFlag;
    ll Value;
    ll BestMoveStateID;
    ll SearchID;
};
class Search {
public:
    ll uniqueCalls=0;
    ll allCalls=0;
    ll bestMove;
    ll bestScore;
    ll _searchID=0;
    ExternBig Eval;
    Board* board;
    Evaluate* evaluate;
    Search(ll maxDepth,Board* brd, Evaluate* eval);
    void GetBestMove();
protected:
    ll _MaxDepth;
    map <ll,TransitionEntry> _TransitionTable;
    virtual void _IterativeDeepening(ll MaxDepth)=0;
    ll Qsearch(ll alpha,ll beta,bool isMax,ll MaxDepth=5);
    void _InsertlloTransitionTable(ll StateID,ll Depth,ll Value,ll HashFlag,ll BestMoveStateID);
    ll _GetFromTransitionTable(ll StateID,ll Depth, ll Alpha, ll Beta);
};



#endif
