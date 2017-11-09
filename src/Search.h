#ifndef CHESSSEARCH_SEARCH_H
#define CHESSSEARCH_SEARCH_H
#define oo  1e9
#include "External/Extern.h"
#include "External/ExternBig.h"
#include "Node.cpp"
#include <unordered_map>
#include <map>
#include <iostream>
#include <algorithm>
#include <set>
#include <time.h>
using namespace std;

class Search {
public:
    ExternBig Eval;
    Search(int maxDepth);
    pair<int,int> GetBestMove(int state_id);
protected:
    int _MaxDepth;
    virtual pair<int,int> _IterativeDeepening(int rootID,int MaxDepth)=0;
    int Qsearch(int state_id,int alpha,int beta,bool isMax);
};


#endif //CHESSSEARCH_SEARCH_H
