#include "PVS.h"

ll PVS::pvsSearch(ll stateID, ll alpha, ll beta, ll depth,bool isMax) {
    this->OpenedStates++;
    ll bestScore = 0;
    if( depth <= 0 ){
        //visitedStates.insert(stateID);
        if (VisitedStates.find(stateID)==VisitedStates.end()) {//not visited b4
            this->cntr++;
            VisitedStates[stateID] = ((isMax) ? 1 : -1) * this->Eval.GetScore(stateID);//Search::Qsearch(stateID, alpha, beta, isMax);
        }
        //else {cout<<"REVISITED!"<<" "<<VisitedStates[stateID]<<endl;}
        return VisitedStates[stateID];
    }

    //Null move
    //TODO DEBUG!!!!
    if(this->doNull && !Search::Eval.IsCheck() && isMax && (depth >=4)&& (depth <9)){
        //Search::Eval.makeNullMove(stateID);

        //to prevent any consequent nulling
        this->doNull = false;

        ll R = depth > 6 ? MAX_R : MIN_R ;
        //search with same state but as a minimizer and with a reduced depth!
        //cout<<endl<<-beta<<" "<<-alpha<<endl;
        ll scorey = - this->pvsSearch(stateID, -beta, -alpha, depth-R-1, !isMax);
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
            //cout<<"NULLING EFFECT!!!"<<" depth levels skipped= "<<depth <<endl;
            return beta;

        }
            //null failed!
        else this->doNull = true;
    }

    vector<ll> nextMoves = this->Eval.GetPossibleMoves(stateID);
    //move ordering making thr PV move the left most
    if (this->PvTable[stateID] == 0) this->PvTable[stateID] = nextMoves[0];

    else if(this->PvTable[stateID] != nextMoves[0])
    {
        for (ll i = 1; i < nextMoves.size(); ++i) {
            if(nextMoves[i] == this->PvTable[stateID]){
                //cout<<"SWAPED "<<i<<endl;
                ll tmp = nextMoves[i];
                nextMoves[i] = nextMoves[0];
                nextMoves[0] = tmp;
                break;
            }
        }
    }
    bestScore = - this->pvsSearch(this->PvTable[stateID], -beta, -alpha, depth-1,!isMax);
    if( bestScore > alpha ) {
        if( bestScore >= beta ){
            return beta;
        }
        alpha = bestScore;

    }
    ll nonPvMoves = nextMoves.size();
    ll score = 0;
    for (ll i = 1; i < nonPvMoves; ++i) {
        //make move
        ll nextState = nextMoves[i];
        //perform a zero-window search
        score = - this->pvsSearch(nextState, -alpha-1, -alpha, depth-1,!isMax); // alphaBeta or zwSearch
        if( score > alpha && score < beta ) {
            // research with window [alpha;beta]
            score = - this->pvsSearch(nextState,-beta, -score, depth-1,!isMax);

            // if( score > alpha )
            //    alpha = score;
        }
        //

        assert(alpha>=bestScore);

        if( score > alpha ) {
            alpha = score;
            this->PvTable[stateID] = nextMoves[i];

        }

        if( score > bestScore ) {
            //move this node with the new bestScore to the leftmost
            //this->PvTable[stateID] = nextMoves[i];
            //
            //if( score >= beta)
            //    return score;
            bestScore = score;
        }
        assert(alpha>=bestScore);
        //
        if( alpha >= beta) {
            //cout << i << endl;
            return alpha;
        }
    }
    return alpha;//bestScore;
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

void PVS::_IterativeDeepening(ll root_id, ll MaxDepth) {
    ll nodeScore;
    bool x = this->doNull;
    //cout<<x<<endl;
    clock_t tStart = clock();
    for (ll i =1; i <= MaxDepth; ++i) {
        //cout<<i<<" ";
        nodeScore = this->pvsSearch(root_id,-oo,oo,i,true);
        this->doNull=x;
        //VisitedStates.clear();
    }
    //pair<ll,ll>mangi=make_pair(nodeScore,PvTable[root_id]);
    this->bestScore = nodeScore;
    this->bestMove = this->PvTable[root_id];

    //PVS::getStatus = make_pair(this->cntr,this->OpenedStates);
    this->uniqueCalls = this->cntr;
    this->allCalls = this->OpenedStates;

    cout<<"PVS       : ["<<bestScore<<','<<bestMove<<','<<uniqueCalls<<","<<OpenedStates<<"] in "<<(clock() - tStart)<<" msec"<<endl;
    this->cntr=0;
    this->OpenedStates=0;
    //PvTable.clear();
    //VisitedStates.clear();
    //return mangi;
}