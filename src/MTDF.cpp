//
// Created by Mangawy on 10/28/2017.
//

#include "MTDF.h"


vector<int> MTDF::_GetSortedPossibleMoves(ll state_id,ll IsMax) {

    vector<int> Pmoves;
    if(this->moveOrder==false) {
        Pmoves = Search::board->allValidMoves;
        //sort(Pmoves.begin(), Pmoves.end());
    }
    else
    {
        vector<int> Pmovesa=Search::board->allValidMoves;
        vector<int> Pmovesc=Search::board->allValidCaptures;
        //sort(Pmovesa.begin(), Pmovesa.end());

        unordered_map<int,int>ex;
        for(int i=0;i<Pmovesc.size();i++)
        {
            Pmoves.push_back(Pmovesc[i]);
            ex[Pmovesc[i]]=5;
        }
        for(int i=0;i<Pmovesa.size();i++)
        {
            if(ex.find(Pmovesa[i])==ex.end())
                Pmoves.push_back(Pmovesa[i]);
        }
    }


    ll BestMoveID=-1;
    if(Search::_TransitionTable.find(state_id)!=Search::_TransitionTable.end())
    {
        BestMoveID=_TransitionTable[state_id].BestMoveStateID;
    }
    if(BestMoveID!=-1)
    {
        for (ll i = 0; i < Pmoves.size(); ++i) {
            if(Pmoves[i]==BestMoveID) {
                Pmoves[i]=Pmoves[0];
                Pmoves[0]=BestMoveID;
                break;
            }
        }
    }
    return Pmoves;
}

void MTDF::_UpdateNode(ll state_id, ll g, ll alpha, ll beta) {
    _MTDfTable[state_id].SearchId=this->_searchID;
    _MTDfTable[state_id].value=g;
    if(g <= alpha)
        _MTDfTable[state_id].upperbound=g;
    if(g > alpha && g < beta)
        _MTDfTable[state_id].lowerbound=g,_MTDfTable[state_id].upperbound=g;
    if(g >= beta)
        _MTDfTable[state_id].lowerbound=g;
}

void MTDF::_IterativeDeepening(ll MaxDepth) {
    Search::tStart = clock();
    //TODO get it from table
    ll firstguess = 0;
    ll root_id=Search::board->key;

    if(Search::_TransitionTable.find(root_id) != Search::_TransitionTable.end()){
        firstguess = Search::_TransitionTable[root_id].Value;
    }
    bool x = this->doNull;
    for (ll d = 1;d<=MaxDepth&&Search::hasTime(); d++) {
        this->Interpt=false;
        firstguess = this->_MTDF(firstguess, d);
        if(this->Interpt==false)
        {
            this->bestScore =  firstguess;
            this->bestMove = Search::_TransitionTable[root_id].BestMoveStateID;
        } else
            cout<<"Mtdf Interrupted at level : "<<d<<endl;
        this->doNull=x;
    }

    this->uniqueCalls = this->EvalStates;
    this->allCalls = this->OpenedStates;
    _MTDfTable.clear();
    cout<<"MTDF      : ["<<bestScore<<','<<bestMove<<','<<EvalStates<<","<<OpenedStates<<"] in "<<(clock() - Search::tStart)/CLOCKS_PER_SEC<<" sec"<<endl;
}

ll MTDF::_MTDF(ll f, ll d) {
    ll g = f;
    ll lowerbound = -oo;
    ll upperbound = +oo;
    //this->_MTDfTable.clear();
    while (lowerbound < upperbound) {
        ll beta = (g == lowerbound) ? g + 1 : g;
        g = this->_AlphaBetaWithMemory(beta - 1, beta, d,true,d, true);
        if (g < beta) {
            upperbound = g;
        } else {
            lowerbound = g;
        }
    }
    Search::_searchID++;
    return g;
}

ll MTDF::_AlphaBetaWithMemory(ll alpha, ll beta,ll d,bool IsMax,ll MaxDepth,bool DoNull) {

    ll state_id=Search::board->key;
    Node entry;

    ll g,_g,a,b;
    if (_MTDfTable.find(state_id)!=_MTDfTable.end()) {
        if(_MTDfTable[state_id].SearchId==this->_searchID) {
            entry = _MTDfTable[state_id];
            if (entry.lowerbound >= beta) {
                return entry.lowerbound;
            }
            if (entry.upperbound <= alpha) {
                return entry.upperbound;
            }
            alpha = max(alpha, entry.lowerbound);
            beta = min(beta, entry.upperbound);
        }
        else
            _MTDfTable[state_id]=entry;
    } else {
        _MTDfTable[state_id]=entry;
    }

    if(this->useTrans)
    if(g=Search::_GetFromTransitionTable(state_id,d,alpha,beta)!=valUNKNOWN)
        return g;
    
    OpenedStates++;
    if (d <= 0 || Search::board->isOver()||Search::hasTime()==false) {
        /* leaf node */
        if(_MTDfTable[state_id].value!=-oo)
            g=_MTDfTable[state_id].value;
        else
        {
            EvalStates++;
            g = Search::Qsearch(alpha,beta,IsMax);
        }
        this->_UpdateNode(state_id,g,alpha,beta);
        Search::_InsertlloTransitionTable(state_id,d,g,hashfEXACT,valUNKNOWN);
        return g;
    }

    vector<int>Pmoves=this->_GetSortedPossibleMoves(state_id,IsMax);
    if(Pmoves.empty()){
        cout<<"Big A7a\n";
        //this->debugEmptyMoves.push_back(make_pair(state_id,board->toFen()));
    }

    ll BestMoveID=-1;
    ll BestMoveScore;
    if(IsMax) {
        ///Null Move
        if(this->doNull && IsMax && (d >=3) && (d < MaxDepth) && !Search::board->isCheck()){
            this->doNull = false;
            ll R = d > 4 ? MAX_R : MIN_R ;
            Search::board->pass();
            ll scorey = this->_AlphaBetaWithMemory(alpha, beta, d-R-1, !IsMax,MaxDepth, true);
            Search::board->undoo();
            if (scorey >= beta) {
                //cout<<"Null Cut-off at depth="<<d<<endl;
                Search::_InsertlloTransitionTable(state_id,d,beta,hashfBETA,valUNKNOWN);
                this->_UpdateNode(state_id,scorey,alpha,beta);
                return beta;
            }
            else this->doNull = true;
        }
        g = -oo;
        a = alpha;
        BestMoveScore=-oo;
        for (ll i = 0; (i < Pmoves.size())&&(g<beta); ++i) {
            //Search::debug.push_back({state_id,Pmoves[i]});
            Search::board->doo(Pmoves[i]);
            _g=_AlphaBetaWithMemory(a, beta, d-1,!IsMax,MaxDepth,true);
            Search::board->undoo();
            //Search::debug.pop_back();
            if(_g>BestMoveScore) {
                BestMoveID=Pmoves[i];
                BestMoveScore=_g;
            }
            g = max(g,_g);
            a = max(a,g);
            if (g >= beta) {
                Search::_InsertlloTransitionTable(state_id,d,beta,hashfBETA,BestMoveID);
                this->_UpdateNode(state_id,g,alpha,beta);
                return beta;
            }
        }
    }
    else {
        BestMoveScore=oo;
        g = +oo;
        b = beta;
        for (ll i = 0; (i < Pmoves.size())&&(g>alpha); ++i) {
            //Search::debug.push_back({state_id,Pmoves[i]});
            Search::board->doo(Pmoves[i]);
            _g=_AlphaBetaWithMemory(alpha, b, d-1,!IsMax,MaxDepth,true);
            Search::board->undoo();
            //Search::debug.pop_back();
            if(_g<BestMoveScore) {
                BestMoveID=Pmoves[i];
                BestMoveScore=_g;
            }
            g = min(g,_g);
            b = min(b,g);
            if (g < alpha) {
                Search::_InsertlloTransitionTable(state_id,d,g,hashfALPHA,BestMoveID);
                this->_UpdateNode(state_id,g,alpha,beta);
                return g;
            }
        }
    }
    Search::_InsertlloTransitionTable(state_id,d,g,hashfEXACT,BestMoveID);
    this->_UpdateNode(state_id,g,alpha,beta);
    return g;
}