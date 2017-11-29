//
// Created by zidan on 11/7/17.
//

#include "AlphaBeta.h"

ll AlphaBeta::alphaBetaSearch(ll alpha, ll beta, ll depth, bool isMax){
    ll stateID = Search::board->key;
    //cout<<stateID<<endl;
    OpenedStates++;
    if( depth == 0 ) {
        this->cntr++;
        //TODO activate Q-Search
        return ((isMax) ? 1 : -1) * Search::Qsearch(alpha, beta, isMax);
        //return ((isMax)?1:-1)*Search::evaluate->evaluate();
    }
    //ToDo rename
    //vector<ll> nextMoves = this->Eval.GetPossibleMoves(stateID);
    vector<int> nextMoves = Search::board->allValidMoves;
    if(nextMoves.size() == 0 ) cout<<"NO MOVES!!!\n";
    ll moves = nextMoves.size();
    ll score = 0;

    for (ll i=0; i< moves;++i)  {
        //ToDO make move
        Search::board->doo(nextMoves[i]);
        score = - this->alphaBetaSearch( -beta, -alpha, depth- 1, !isMax);
        //ToDO unmake move
        Search::board->undoo();

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

void AlphaBeta::_IterativeDeepening(ll MaxDepth) {
    ll nodeScore;
    clock_t tStart = clock();
    ll root_id=Search::board->key;
    for (ll i = 1; i <= MaxDepth; ++i) {
        nodeScore = this->alphaBetaSearch(-oo,oo,i,true);
    }
    //pair<ll,ll>baseline=make_pair(nodeScore,MoveTable[root_id]);
    this->bestScore = nodeScore;
    this->bestMove = this->MoveTable[root_id];
    this->uniqueCalls = this->cntr;
    this->allCalls = this->OpenedStates;

    cout<<"AlphaBeta : ["<<bestScore<<','<<bestMove<<','<<cntr<<","<<OpenedStates<<"] in "<<(clock() - tStart)/CLOCKS_PER_SEC<<" sec"<<endl;
    //cout<<"AVG TIME  "<<(Search::evaluate->xx)/(Search::evaluate->xxx)<<endl;

    //MoveTable.clear();
    //return baseline;
}
