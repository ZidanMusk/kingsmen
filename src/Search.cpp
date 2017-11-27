#include "Search.h"

Search::Search(ll maxDepth)
{this->_MaxDepth=maxDepth;}
void Search::GetBestMove(ll state_id) {return this->_IterativeDeepening(state_id,this->_MaxDepth);}
ll Search::Qsearch(ll state_id,ll alpha, ll beta,bool isMax,ll MaxDepth) {
    ll score=this->Eval.GetScore(state_id);
    if(MaxDepth==0)
        return score;
    if(isMax)
    {
        if(score>=beta)
            return score;
        alpha=max(alpha,score);
        vector<ll>capturingMoves=this->Eval.GetCapturingMoves(state_id);
        for (ll i = 0; i < (capturingMoves.size())&&score<beta; ++i) {
            score=max(score,Qsearch(capturingMoves[i],alpha,beta,!isMax,MaxDepth-1));
            alpha=max(score,alpha);
        }
        return score;
    }
    else
    {
        if(score<=alpha)
            return score;
        beta=min(beta,score);
        vector<ll>capturingMoves=this->Eval.GetCapturingMoves(state_id);
        for (ll i = 0; i < (capturingMoves.size())&&score>alpha; ++i) {
            score=min(score,Qsearch(capturingMoves[i],alpha,beta,!isMax,MaxDepth-1));
            beta=min(score,beta);
        }
        return score;
    }
}

void Search::_InsertlloTransitionTable(ll StateID, ll Depth, ll Value, ll HashFlag, ll BestMoveStateID) {
    if(_TransitionTable.find(StateID)==_TransitionTable.end())
    {
        TransitionEntry  ENTRY;
        ENTRY.Depth=Depth;
        ENTRY.HashFlag=HashFlag;
        ENTRY.Value=Value;
        ENTRY.SearchID=this->_searchID;
        ENTRY.BestMoveStateID=BestMoveStateID;
        _TransitionTable[StateID]=ENTRY;
    }
    else
    {
        TransitionEntry  ENTRY=_TransitionTable[StateID];
        if(Depth>ENTRY.Depth)
        {
            ENTRY.Depth=Depth;
            ENTRY.HashFlag=HashFlag;
            ENTRY.Value=Value;
            ENTRY.BestMoveStateID=BestMoveStateID;
            ENTRY.SearchID=this->_searchID;
            _TransitionTable[StateID]=ENTRY;
        } else if (ENTRY.SearchID==this->_searchID)
        {
            ENTRY.Depth=Depth;
            ENTRY.HashFlag=HashFlag;
            ENTRY.Value=Value;
            ENTRY.BestMoveStateID=BestMoveStateID;
            ENTRY.SearchID=this->_searchID;
            _TransitionTable[StateID]=ENTRY;
        }
    }
}

ll Search::_GetFromTransitionTable(ll StateID, ll Depth, ll Alpha, ll Beta) {
    if(_TransitionTable.find(StateID)==_TransitionTable.end())
        return valUNKNOWN;
    TransitionEntry  ENTRY=_TransitionTable[StateID];
    if(ENTRY.SearchID==this->_searchID)
        return valUNKNOWN;

    if (ENTRY.Depth >= Depth) {
        if (ENTRY.HashFlag == hashfEXACT) {
            return ENTRY.Value;
        }
        if ((ENTRY.HashFlag == hashfALPHA) && (ENTRY.Value <= Alpha)) {
            return Alpha;
        }
        if ((ENTRY.HashFlag == hashfBETA) && (ENTRY.Value >= Beta)) {
            return Beta;
        }
    }
    return valUNKNOWN;
}