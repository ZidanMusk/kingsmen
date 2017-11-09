#ifndef MTD_F_MTDF_H
#define MTD_F_MTDF_H

#include "Search.h"

class MTDF : public Search {
public:
    int OpenedStates=0;
    int EvalStates=0;
    MTDF(int maxDepth):Search(maxDepth) {};
private:
    unordered_map<int,Node>_MTDfTable;
    unordered_map<int,Node>_VisitedState;
    map<pair<int,int>,int>_DeepeningTable;
    pair<int,int> _IterativeDeepening(int root_id,int MaxDepth);
    int _MTDF(int root_id, int f, int d);
    int _AlphaBetaWithMemory(int state_id, int alpha, int beta,int d,bool IsMax,int MaxDepth,bool DoNull);
    void _UpdateNode(int state_id,int g ,int alpha, int beta);
    vector<int> _GetSortedPossibleMoves(int state_id,int IsMax);
    static bool _MySortFunMax(pair<int,int> i, pair<int,int> j);
    static bool _MySortFunMin(pair<int,int> i, pair<int,int> j);
};


#endif //MTD_F_MTDF_H
