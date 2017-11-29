#include "PVS.h"

ll PVS::pvsSearch(ll alpha, ll beta, ll depth,bool isMax) {
    ll stateID=Search::board->key;
    this->OpenedStates++;
    ll bestScore = 0;
    if( depth <= 0 ){
        if (VisitedStates.find(stateID)==VisitedStates.end()) {//not visited b4
            this->cntr++;
            VisitedStates[stateID] = ((isMax) ? 1 : -1) * Search::Qsearch(alpha,beta,isMax);
            //Search::Qsearch(stateID, alpha, beta, isMax);
        }
        return VisitedStates[stateID];
    }

    //Null move
    //TODO DEBUG!!!!
    if(this->doNull && isMax && (depth >=4)&& (depth <9)){
        //Search::Eval.makeNullMove(stateID);

        //to prevent any consequent nulling
        this->doNull = false;

        ll R = depth > 6 ? MAX_R : MIN_R ;
        //search with same state but as a minimizer and with a reduced depth!
        //cout<<endl<<-beta<<" "<<-alpha<<endl;
        Search::board->pass();
        ll scorey = - this->pvsSearch(-beta, -alpha, depth-R-1, !isMax);
        Search::board->pass();
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
            //cout<<"NULLING EFFECT!!!"<<" depth levels skipped= "<<depth <<endl;
            return beta;

        }
            //null failed!
        else this->doNull = true;
    }

    vector<int> nextMoves = Search::board->allValidMoves;
    if(nextMoves.size()){
        //move ordering making thr PV move the left most
        if (this->PvTable.find(stateID) == this->PvTable.end()){
            this->PvTable[stateID] = nextMoves[0];
        }

        else if(this->PvTable[stateID] != nextMoves[0]) {
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
   }
    else{
        cout<<"start from initial state:"<<endl;
        for(int i=0;i<debug.size();++i) {
            cout << (unsigned ll)debug[i].first << " -> " << debug[i].second << endl;
        }
        cout<<"until reached state with no moves: "<<(unsigned ll)stateID<<endl;

    }

    this->debug.push_back(make_pair(stateID,this->PvTable[stateID]));

    Search::board->doo(this->PvTable[stateID]);
    bestScore = - this->pvsSearch(-beta, -alpha, depth-1,!isMax);
    Search::board->undoo();

    this->debug.pop_back();

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
        this->debug.push_back(make_pair(stateID,nextState));

        Search::board->doo(nextState);
        score = - this->pvsSearch(-alpha-1, -alpha, depth-1,!isMax); // alphaBeta or zwSearch
        Search::board->undoo();

        this->debug.pop_back();

        if( score > alpha && score < beta ) {
            // research with window [alpha;beta]
            this->debug.push_back(make_pair(stateID,nextState));

            Search::board->doo(nextState);
            score = - this->pvsSearch(-beta, -score, depth-1,!isMax);
            Search::board->undoo();

            this->debug.pop_back();


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

void PVS::_IterativeDeepening(ll MaxDepth) {
    ll root_id=Search::board->key;
    ll nodeScore;
    bool x = this->doNull;
    //cout<<x<<endl;
    clock_t tStart = clock();
    for (ll i =1; i <= MaxDepth; ++i) {
        //cout<<i<<" ";
        nodeScore = this->pvsSearch(-oo,oo,i,true);
        this->doNull=x;
        //VisitedStates.clear();
    }
    //pair<ll,ll>mangi=make_pair(nodeScore,PvTable[root_id]);
    this->bestScore = nodeScore;
    this->bestMove = this->PvTable[root_id];

    //PVS::getStatus = make_pair(this->cntr,this->OpenedStates);
    this->uniqueCalls = this->cntr;
    this->allCalls = this->OpenedStates;

    cout<<"PVS       : ["<<bestScore<<','<<bestMove<<','<<uniqueCalls<<","<<OpenedStates<<"] in "<<(clock() - tStart)/CLOCKS_PER_SEC<<" sec"<<endl;
    this->cntr=0;
    this->OpenedStates=0;
    PvTable.clear();
    VisitedStates.clear();
    //return mangi;
}