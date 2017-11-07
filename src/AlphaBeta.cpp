//
// Created by zidan on 11/7/17.
//

#include "AlphaBeta.h"

int AlphaBeta::alphaBetaSearch(int stateID, int alpha, int beta, int depth, bool isMax){
    if( depth == 0 ) {
        this->cntr++;
        return ((isMax)?1:-1)*this->Eval.GetScore(stateID);
    }
    vector<int> nextMoves = this->Eval.GetPossibleMoves(stateID);
    int moves = nextMoves.size();
    int score = 0;
    for (int i=0; i< moves;++i)  {
        //make move
        int nextState = nextMoves[i];
        score = - this->alphaBetaSearch(nextState, -beta, -alpha, depth- 1, !isMax);
        if( score >= beta ){
            return beta;   //  fail hard beta-cutoff
        }
        if( score > alpha ){
            this->MoveTable[stateID] = nextMoves[i];
            alpha = score;
        }
    }
    return alpha;
}

pair<int,int> AlphaBeta::_IterativeDeepening(int root_id, int MaxDepth) {
    int nodeScore;
    for (int i = 1; i <= MaxDepth; ++i) {
        nodeScore = this->alphaBetaSearch(root_id,-oo,oo,i,true);
    }
    pair<int,int>baseline=make_pair(nodeScore,MoveTable[root_id]);
    cout<<"EvalStates : "<<this->cntr<<" Of 33"<<endl;
    MoveTable.clear();
    return baseline;
}
