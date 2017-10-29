//
// Created by Mangawy on 10/28/2017.
//

#include "MTDF.h"

bool MTDF::_MySortFunMax(pair<int,int> i, pair<int,int> j) {return i.second>j.second;}
bool MTDF::_MySortFunMin(pair<int,int> i, pair<int,int> j) {return i.second<j.second;}
vector<int> MTDF::_GetSortedPossibleMoves(int state_id) {
    if(_DeepeningTableLastIter.find(state_id)!=_DeepeningTableLastIter.end())
        return _DeepeningTableLastIter[state_id];
    vector<int> Pmoves=Search::Eval.GetPossibleMoves(state_id);
    return Pmoves;
}
void MTDF::_UpdateNode(int state_id, int g, int alpha, int beta) {
    _MTDfTable[state_id].value=g;
    if(g <= alpha)
        _MTDfTable[state_id].upperbound=g;
    if(g > alpha && g < beta)
        _MTDfTable[state_id].lowerbound=g,_MTDfTable[state_id].upperbound=g;
    if(g >= beta)
        _MTDfTable[state_id].lowerbound=g;
}
pair<int,int> MTDF::_IterativeDeepening(int root_id,int MaxDepth)
{
    int firstguess = 0;
    for (int d = 1;d<=MaxDepth; d++) {
        firstguess = this->_MTDF(root_id, firstguess, d);
    }
    pair<int,int> Bibi=make_pair(firstguess,_DeepeningTableLastIter[1][0]);
    _DeepeningTableLastIter.clear();
    _DeepeningTableCurIter.clear();
    _MTDfTable.clear();
    cout<<"EvalStates : "<<this->EvalStates<<" Of 33"<<endl;
    return Bibi;
}
int MTDF::_MTDF(int root_id, int f, int d)
{
    int g = f;
    int lowerbound = -oo;
    int upperbound = +oo;
    this->_MTDfTable.clear();
    this->_DeepeningTableCurIter.clear();
    while (lowerbound < upperbound) {
        int beta = (g == lowerbound) ? g + 1 : g;
        g = this->_AlphaBetaWithMemory(root_id, beta - 1, beta, d,true,d);
        if (g < beta) {
            upperbound = g;
        } else {
            lowerbound = g;
        }
    }
    this->_DeepeningTableLastIter=this->_DeepeningTableCurIter;
    return g;
}
int MTDF::_AlphaBetaWithMemory(int state_id, int alpha, int beta,int d,bool IsMax,int MaxDepth) {


    Node entry;
    int g,a,b;
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
        OpenedStates++;
        _MTDfTable[state_id]=entry;
    }

    if (d == 0 || Search::Eval.IsGameFinished() || Search::Eval.hasTime() == false) {
        /* leaf node */
        if(_MTDfTable[state_id].value!=-oo)
            g=_MTDfTable[state_id].value;
        else
        {
            EvalStates++;
            g = Search::Eval.GetScore(state_id);
        }
        this->_UpdateNode(state_id,g,alpha,beta);
        return g;
    }

    vector<int>Pmoves=this->_GetSortedPossibleMoves(state_id);
    vector<pair<int,int>>Pmoves_State_Score;
    if(IsMax)
    {
        g = -oo;
        a = alpha;
        for (int i = 0; (i < Pmoves.size())&&(g<beta); ++i) {
            g = max(g,_AlphaBetaWithMemory(Pmoves[i], a, beta, d-1,!IsMax,MaxDepth));
            Pmoves_State_Score.push_back(make_pair(Pmoves[i],g));
            a = max(a,g);
        }
    } else
    {
        g = +oo;
        b = beta;
        for (int i = 0; (i < Pmoves.size())&&(g>alpha); ++i) {
            g = min(g,_AlphaBetaWithMemory(Pmoves[i], alpha, b, d-1,!IsMax,MaxDepth));
            Pmoves_State_Score.push_back(make_pair(Pmoves[i],g));
            b = min(b,g);
        }
    }
    if(IsMax)sort(Pmoves_State_Score.begin(),Pmoves_State_Score.end(),_MySortFunMax);
    else sort(Pmoves_State_Score.begin(),Pmoves_State_Score.end(),_MySortFunMin);
    vector<int>tmp;
    for (int j = 0; j < Pmoves_State_Score.size(); ++j) {
        tmp.push_back(Pmoves_State_Score[j].first);
    }
    _DeepeningTableCurIter[state_id]=tmp;

    this->_UpdateNode(state_id,g,alpha,beta);
    return g;
}