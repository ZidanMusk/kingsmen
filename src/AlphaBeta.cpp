//
// Created by zidan on 11/7/17.
//

#include "AlphaBeta.h"

ll AlphaBeta::alphaBetaSearch(ll stateID, ll alpha, ll beta, ll depth, bool isMax){
    OpenedStates++;
    if( depth == 0 ) {
        this->cntr++;
        //return ((isMax) ? 1 : -1) * Search::Qsearch(stateID, alpha, beta, isMax);
        return ((isMax)?1:-1)*this->Eval.GetScore(stateID);
    }
    //ToDo rename
    vector<ll> nextMoves = this->Eval.GetPossibleMoves(stateID);
    ll moves = nextMoves.size();
    ll score = 0;
    for (ll i=0; i< moves;++i)  {
        //ToDO make move
        ll nextState = nextMoves[i];
        score = - this->alphaBetaSearch(nextState, -beta, -alpha, depth- 1, !isMax);
        //ToDO unmake move
        if( score >= beta ){
            return beta;   //  fail hard beta-cutoff
        }
        if( score > alpha ){
            this->MoveTable[stateID] = nextMoves[i];
            alpha = score;
        }//pass
        if (alpha >=beta) return alpha;
    }
    return alpha;
}

void AlphaBeta::getPvPath(ll root){
    ll i=this->MoveTable[root];
    ll count=0;
    cout<<"PV path: ";
    while(i != 0){
        cout<<i<<" ";
        i = this->MoveTable[i];
        count++;
    }
    cout<<endl<<"Path length: "<<count<<endl;
}

void AlphaBeta::_IterativeDeepening(ll root_id, ll MaxDepth) {
    ll nodeScore;
    clock_t tStart = clock();
    for (ll i = 1; i <= MaxDepth; ++i) {
        nodeScore = this->alphaBetaSearch(root_id,-oo,oo,i,true);
    }
    //pair<ll,ll>baseline=make_pair(nodeScore,MoveTable[root_id]);
    this->bestScore = nodeScore;
    this->bestMove = this->MoveTable[root_id];
    this->uniqueCalls = this->cntr;
    this->allCalls = this->OpenedStates;

    cout<<"AlpahBeta : ["<<bestScore<<','<<bestMove<<','<<cntr<<","<<OpenedStates<<"] in "<<(clock() - tStart)<<" msec"<<endl;

    //MoveTable.clear();
    //return baseline;
}
