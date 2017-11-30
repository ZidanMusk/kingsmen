#include "Search.h"

Search::Search(ll maxDepth,Board* brd, Evaluate* eval,int timeL) {
    this->_MaxDepth=maxDepth;
    this->board = brd;
    this->evaluate = eval;
    this->timeLimit=timeL;
}
void Search::GetBestMove() {return this->_IterativeDeepening(this->_MaxDepth);}

ll Search::Qsearch(ll alpha, ll beta,bool isMax,ll MaxDepth) {
    ll state_id = Search::board->key;
    ll score=Search::evaluate->evaluate();
    if(MaxDepth==0 || Search::board->isOver())
        return score;
    if(isMax)
    {
        if(score>=beta)
            return score;
        alpha = max(alpha,score);
        vector <int> capturingMoves = Search::board->allValidCaptures;

        for (ll i = 0; i < (capturingMoves.size())&&score<beta; ++i) {
            Search::board->doo(capturingMoves[i]);
            score=max(score,Qsearch(alpha,beta,!isMax,MaxDepth-1));
            Search::board->undoo();
            alpha=max(score,alpha);
        }
        return score;
    }
    else
    {
        if(score<=alpha)
            return score;
        beta=min(beta,score);
        vector <int> capturingMoves = Search::board->allValidCaptures;
        for (ll i = 0; i < (capturingMoves.size())&&score>alpha; ++i) {
            Search::board->doo(capturingMoves[i]);
            score=min(score,Qsearch(alpha,beta,!isMax,MaxDepth-1));
            Search::board->undoo();
            beta=min(score,beta);
        }
        return score;
    }
}

void Search::_InsertlloTransitionTable(ll StateID, ll Depth, ll Value, ll HashFlag, ll BestMoveStateID) {
    if(_TransitionTable.size() > 500000) _TransitionTable.clear();
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
            if(Search::evaluate->evaluate()!=ENTRY.Value&&Depth==0)
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