//
// Created by zidan on 11/7/17.
//

#include "AlphaBeta.h"

ll AlphaBeta::alphaBetaSearch(ll alpha, ll beta, ll depth, bool isMax){
    ll stateID = Search::board->key;
    OpenedStates++;
    if(Search::board->isOver()){
        this->debugIsOver.push_back(make_pair(stateID,board->toFen()));
    }
    //TODO isOVer()
    if(depth == 0 || Search::board->isOver()) {
        this->cntr++;
        return ((isMax) ? 1 : -1) * Search::Qsearch(alpha, beta, isMax);
    }
    vector<int> nextMoves = Search::board->allValidMoves;
    if(nextMoves.empty()) cout<<"NO MOVES!!!\n";
    ll moves = nextMoves.size();
    ll score = 0;
    for (ll i=0; i< moves;++i)  {
        Search::board->doo(nextMoves[i]);
        score = - this->alphaBetaSearch( -beta, -alpha, depth- 1, !isMax);
        Search::board->undoo();
        if( score >= beta ){
            return beta;
        }
        if( score > alpha ){
            this->MoveTable[stateID] = nextMoves[i];
            alpha = score;
        }
        if (alpha >=beta) return alpha;
    }
    return alpha;
}

void AlphaBeta::getPvPath(ll root){
    ll i = this->MoveTable[root];
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
    ll root_id = Search::board->key;
    for (ll i = 1; i <= MaxDepth; ++i) {
        nodeScore = this->alphaBetaSearch(-oo, oo, i, true);
    }
    this->bestScore = nodeScore;
    this->bestMove = this->MoveTable[root_id];
    this->uniqueCalls = this->cntr;
    this->allCalls = this->OpenedStates;
    cout << "AlphaBeta : [" << bestScore << ',' << bestMove << ',' << cntr << "," << OpenedStates << "] in "
         << (clock() - tStart) / CLOCKS_PER_SEC << " sec" << endl;
    //cout<<"AVG TIME  "<<(Search::evaluate->xx)/(Search::evaluate->xxx)<<endl;

    MoveTable.clear();
    this->cntr = 0;
    this->OpenedStates = 0;

}
