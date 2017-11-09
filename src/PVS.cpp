#include "PVS.h"


int PVS::pvsSearch(int stateID, int alpha, int beta, int depth,bool isMax) {
    OpenedStates++;
    int bestScore = 0;
    if( depth <= 0 ){
        //visitedStates.insert(stateID);
        if (VisitedStates.find(stateID)==VisitedStates.end()) {//not visited b4
            this->cntr++;
            VisitedStates[stateID] = ((isMax) ? 1 : -1) * Search::Qsearch(stateID, alpha, beta, isMax);
        }
        return VisitedStates[stateID];
    } //qsearch(alpha, beta);
    vector<int> nextMoves = this->Eval.GetPossibleMoves(stateID);
    // using fail soft with negamax:
    //make the PV-Node the leftmost
    if (this->PvTable[stateID] == 0) this->PvTable[stateID] = nextMoves[0];

    else if(this->PvTable[stateID] != nextMoves[0])
    {
        for (int i = 1; i < nextMoves.size(); ++i) {
            if(nextMoves[i] == this->PvTable[stateID]){
                int tmp = nextMoves[i];
                nextMoves[i] = nextMoves[0];
                nextMoves[0] = tmp;
                break;
            }
        }
    }
    bestScore = - this->pvsSearch(this->PvTable[stateID], -beta, -alpha, depth-1,!isMax);
    if( bestScore > alpha ) {
        if( bestScore >= beta )
            return bestScore;
        alpha = bestScore;
    }
    int nonPvMoves = nextMoves.size();
    int score = 0;
    for (int i = 1; i < nonPvMoves; ++i) {
        //make move
        int nextState = nextMoves[i];
        //perform a zero-window search
        score = - this->pvsSearch(nextState, -alpha-1, -alpha, depth-1,!isMax); // alphaBeta or zwSearch
        if( score > alpha && score < beta ) {
            // research with window [alpha;beta]
            score = - this->pvsSearch(nextState,-beta, -alpha, depth-1,!isMax);

            if( score > alpha )
                alpha = score;
        }
        if( score > bestScore ) {
            //move this node with the new bestScore to the leftmost
            this->PvTable[stateID] = nextMoves[i];
            if( score >= beta)
                return score;
            bestScore = score;
        }
    }
    return bestScore;
}

pair<int,int> PVS::_IterativeDeepening(int root_id, int MaxDepth) {
    int nodeScore;
    clock_t tStart = clock();
    for (int i = 1; i <= MaxDepth; ++i) {
        nodeScore = this->pvsSearch(root_id,-oo,oo,i,true);
        VisitedStates.clear();
    }
    pair<int,int>mangi=make_pair(nodeScore,PvTable[root_id]);
    cout<<"EvalStates : ["<<this->cntr<<","<<OpenedStates<<"] in "<<clock() - tStart-Eval.TreeCreationTime<<" ms"<<endl;

    PvTable.clear();
    VisitedStates.clear();
    return mangi;
}