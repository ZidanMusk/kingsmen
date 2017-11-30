#include "PVS.h"

ll PVS::pvsSearch(ll alpha, ll beta, ll depth,bool isMax, ll maxDepth) {
    ll stateID= Search::board->key;
    vector<int> nextMoves = Search::board->allValidMoves;
    this->OpenedStates++;
    ll bestScore = 0;
    if( depth <= 0 || Search::board->isOver()||Search::hasTime()==false){
        if (VisitedStates.find(stateID)==VisitedStates.end()) {//not visited b4
            this->cntr++;
            VisitedStates[stateID] = ((isMax) ? 1 : -1) * Search::Qsearch(alpha,beta,isMax);//!isMax
        }
        return VisitedStates[stateID];
    }
    ///Null move
    if(this->doNull && isMax && (depth >=3)&& (depth < maxDepth) && !Search::board->isCheck()){
        //to prevent any consequent nulling
        this->doNull = false;
        ll R = depth > 4 ? MAX_R : MIN_R ;
        //search with same state but as a minimizer and with a reduced depth!
        Search::board->pass();
        ll scorey = - this->pvsSearch(-beta, -beta+1, depth-R-1, !isMax,maxDepth);
        Search::board->undoo();
        if (scorey >= beta) { // reduce the depth in case of fail-high
            //depth -= DR;
            //if( depth <= 0 ){
            //visitedStates.insert(stateID);
            /*if (VisitedStates.find(stateID)==VisitedStates.end()) {//not visited b4
                this->cntr++;
                VisitedStates[stateID] = ((isMax) ? 1 : -1) * Search::Qsearch(stateID, alpha, beta, isMax);
            }
            return VisitedStates[stateID];*/
            //}
            //cout << "NULLING EFFECT!!!" << " depth levels skipped= " << depth << endl;
            return beta;

        }//null failed!
        else this->doNull = true;
    }
    if(!nextMoves.empty()){
        //move ordering making thr PV move the left most
        if (this->PvTable.find(stateID) == this->PvTable.end()){
            this->PvTable[stateID] = nextMoves[0];
        }
        else if(this->PvTable[stateID] != nextMoves[0]) {
            for (ll i = 1; i < nextMoves.size(); ++i) {
                if(nextMoves[i] == this->PvTable[stateID]){
                    int tmp = nextMoves[i];
                    nextMoves[i] = nextMoves[0];
                    nextMoves[0] = tmp;
                    break;
                }
            }
        }
   }
    else{
        /*cout<<"start from initial state:"<<endl;
        for(int i=0;i<debug.size();++i) {
            cout << (unsigned ll)debug[i].first << " -> " << debug[i].second << endl;
        }
        cout<<"until reached state with no moves: "<<(unsigned ll)stateID<<endl;*/
        cout<<"VERY BIG A7A!\n";
    }

    //this->debug.push_back(make_pair(stateID,this->PvTable[stateID]));

    Search::board->doo(this->PvTable[stateID]);
    bestScore = - this->pvsSearch(-beta, -alpha, depth-1, !isMax,maxDepth);
    Search::board->undoo();

    //this->debug.pop_back();

    if( bestScore > alpha ) {
        if( bestScore >= beta ){
            return beta;
        }
        alpha = bestScore;
    }
    ll nonPvMoves = nextMoves.size();
    ll score = 0;
    for (ll i = 1; i < nonPvMoves; ++i) {
        int nextState = nextMoves[i];
        //perform a zero-window search
        //this->debug.push_back(make_pair(stateID,nextState));

        Search::board->doo(nextState);
        score = - this->pvsSearch(-alpha-1, -alpha, depth-1,!isMax,maxDepth); // alphaBeta or zwSearch
        Search::board->undoo();

        //this->debug.pop_back();

        if( score > alpha && score < beta ) {
            // research with window [alpha;beta]
            //this->debug.push_back(make_pair(stateID,nextState));

            Search::board->doo(nextState);
            score = - this->pvsSearch(-beta, -score, depth-1,!isMax,maxDepth);
            Search::board->undoo();

            //this->debug.pop_back();
        }

        if( score > alpha ) {
            alpha = score;
            this->PvTable[stateID] = nextMoves[i];
        }
        if( score > bestScore ) {
            bestScore = score;
        }
        if( alpha >= beta) {
            return alpha;
        }
    }
    return alpha;
}

void PVS::getPvPath(ll root){
    ll i=this->PvTable[root];
    ll count=0;
    cout<<"PV path: ";
    while(i != 0){
        cout<<i<<" ";
        i = this->PvTable[i];
        count++;
    }
    cout<<endl<<"Path length: "<<count<<endl;
}

void PVS::_IterativeDeepening(ll MaxDepth) {
    ll root_id=Search::board->key;
    ll nodeScore;
    this->cntr=0;
    this->OpenedStates=0;
    bool x = this->doNull;
    Search::tStart= clock();
    for (ll i =1; i <= MaxDepth&&Search::hasTime(); ++i) {
        this->Interpt=false;
        nodeScore = this->pvsSearch(-oo,oo,i,true,i);
        if(this->Interpt==false)
        {
            this->bestScore = nodeScore;
            this->bestMove = this->PvTable[root_id];
        } else
            cout<<"PVS  Interrupted at level : "<<i<<endl;
        this->doNull=x;
    }

    this->uniqueCalls = this->cntr;
    this->allCalls = this->OpenedStates;

    //PvTable.clear();
    VisitedStates.clear();
    cout<<"PVS       : ["<<bestScore<<','<<bestMove<<','<<uniqueCalls<<","<<OpenedStates<<"] in "<<(clock() - Search::tStart)/CLOCKS_PER_SEC<<" sec"<<endl;

}