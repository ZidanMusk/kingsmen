#ifndef CHESSSEARCH_SEARCH_H
#define CHESSSEARCH_SEARCH_H
#define oo  1e9
#include "External/Extern.h"
#include "Node.cpp"
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

class Search {
public:
    Search(int maxDepth);
    pair<int,int> GetBestMove(int state_id);
protected:
    Extern Eval;
    int _MaxDepth;
    virtual pair<int,int> _IterativeDeepening(int rootID,int MaxDepth)=0;
};


#endif //CHESSSEARCH_SEARCH_H
