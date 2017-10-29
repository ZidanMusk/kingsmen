#ifndef CHESS_SEARCH_PVS_H
#define CHESS_SEARCH_PVS_H

#include "Search.h"

class PVS : public Search{
public:
    PVS(int maxDepth):Search(maxDepth) {}

private:
    unordered_map <int,int> PvTable;
    int cntr=0;
    set<int>visitedStates;
    int pvsSearch(int stateID, int alpha, int beta, int depth, bool isMax);
    pair<int,int> _IterativeDeepening(int root_id,int MaxDepth);

};


#endif //CHESS_SEARCH_PVS_H
