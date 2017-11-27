//
// Created by Mangawy on 10/28/2017.
//

#include "MTDF.h"


vector<ll> MTDF::_GetSortedPossibleMoves(ll state_id,ll IsMax) {
    vector<ll> Pmoves=Search::Eval.GetPossibleMoves(state_id);
    if(this->useTrans==false)
        return Pmoves;
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
    _MTDfTable[state_id].value=g;
    if(g <= alpha)
        _MTDfTable[state_id].upperbound=g;
    if(g > alpha && g < beta)
        _MTDfTable[state_id].lowerbound=g,_MTDfTable[state_id].upperbound=g;
    if(g >= beta)
        _MTDfTable[state_id].lowerbound=g;
}
void MTDF::_IterativeDeepening(ll root_id,ll MaxDepth)
{
    clock_t tStart = clock();
    ll firstguess = 0;
    for (ll d = 1;d<=MaxDepth; d++) {
        firstguess = this->_MTDF(root_id, firstguess, d);
    }
    this->bestScore =  firstguess;
    this->bestMove = Search::_TransitionTable[root_id].BestMoveStateID;
    this->uniqueCalls = this->EvalStates;
    this->allCalls = this->OpenedStates;
    _MTDfTable.clear();
    cout<<"MTDF      : ["<<bestScore<<','<<bestMove<<','<<EvalStates<<","<<OpenedStates<<"] in "<<(clock() - tStart)<<" msec"<<endl;

}
ll MTDF::_MTDF(ll root_id, ll f, ll d)
{
    ll g = f;
    ll lowerbound = -oo;
    ll upperbound = +oo;
    this->_MTDfTable.clear();
    while (lowerbound < upperbound) {
        ll beta = (g == lowerbound) ? g + 1 : g;
        g = this->_AlphaBetaWithMemory(root_id, beta - 1, beta, d,true,d, true);
        if (g < beta) {
            upperbound = g;
        } else {
            lowerbound = g;
        }
    }
    Search::_searchID++;
    return g;
}
ll MTDF::_AlphaBetaWithMemory(ll state_id, ll alpha, ll beta,ll d,bool IsMax,ll MaxDepth,bool DoNull) {

    Node entry;

    ll g,_g,a,b;
    if (_MTDfTable.find(state_id)!=_MTDfTable.end()) {
        entry=_MTDfTable[state_id];
        if (entry.lowerbound >= beta) {
            return entry.lowerbound;
        }
        if (entry.upperbound <= alpha) {
            return entry.upperbound;
        }
        alpha = max(alpha, entry.lowerbound);
        beta  = min(beta, entry.upperbound);
    } else {
        _MTDfTable[state_id]=entry;
    }

    if(this->useTrans)
    if(g=Search::_GetFromTransitionTable(state_id,d,alpha,beta)!=valUNKNOWN)
        return g;
    
    OpenedStates++;
    if (d <= 0 || Search::Eval.IsGameFinished() || Search::Eval.hasTime() == false) {
        /* leaf node */
        if(_MTDfTable[state_id].value!=-oo)
            g=_MTDfTable[state_id].value;
        else
        {
            EvalStates++;
            g = Search::Qsearch(state_id,alpha,beta,IsMax);
        }
        this->_UpdateNode(state_id,g,alpha,beta);
        if(this->useTrans)
        Search::_InsertlloTransitionTable(state_id,d,g,hashfEXACT,valUNKNOWN);
        return g;
    }

    vector<ll>Pmoves=this->_GetSortedPossibleMoves(state_id,IsMax);
    ll BestMoveID=-1;
    ll BestMoveScore;
    if(IsMax)
    {
        //Null Move
        if(this->doNull && !Search::Eval.IsCheck() && IsMax && (d >=4)&& (d <9)){

            this->doNull = false;
            ll R = d > 6 ? MAX_R : MIN_R ;
            ll scorey = this->_AlphaBetaWithMemory(state_id, alpha, beta, d-R-1, !IsMax,MaxDepth, true);
            if (scorey >= beta) {
                if(this->useTrans)
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

            _g=_AlphaBetaWithMemory(Pmoves[i], a, beta, d-1,!IsMax,MaxDepth,true);

            if(_g>BestMoveScore)
            {
                BestMoveID=Pmoves[i];
                BestMoveScore=_g;
            }
            g = max(g,_g);
            a = max(a,g);
            if(this->useTrans)
                if (g >= beta) {
                    Search::_InsertlloTransitionTable(state_id,d,beta,hashfBETA,BestMoveID);
                    this->_UpdateNode(state_id,g,alpha,beta);
                    return beta;
                }
        }
    } else
    {
        BestMoveScore=oo;
        g = +oo;
        b = beta;
        for (ll i = 0; (i < Pmoves.size())&&(g>alpha); ++i) {

            _g=_AlphaBetaWithMemory(Pmoves[i], alpha, b, d-1,!IsMax,MaxDepth,true);

            if(_g<BestMoveScore)
            {
                BestMoveID=Pmoves[i];
                BestMoveScore=_g;
            }
            g = min(g,_g);
            b = min(b,g);
            if(this->useTrans)
                if (g < alpha) {
                    Search::_InsertlloTransitionTable(state_id,d,g,hashfALPHA,BestMoveID);
                    this->_UpdateNode(state_id,g,alpha,beta);
                    return g;
                }
        }
    }
    if(this->useTrans)
            Search::_InsertlloTransitionTable(state_id,d,g,hashfEXACT,BestMoveID);

    this->_UpdateNode(state_id,g,alpha,beta);
    return g;
}
