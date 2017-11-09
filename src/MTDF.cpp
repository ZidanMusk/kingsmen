//
// Created by Mangawy on 10/28/2017.
//

#include "MTDF.h"

bool MTDF::_MySortFunMax(pair<int,int> i, pair<int,int> j) {return i.second>j.second;}
bool MTDF::_MySortFunMin(pair<int,int> i, pair<int,int> j) {return i.second<j.second;}
vector<int> MTDF::_GetSortedPossibleMoves(int state_id,int IsMax) {
    vector<int> Pmoves=Search::Eval.GetPossibleMoves(state_id);
    return Pmoves;
    vector<pair<int,int>>Pmoves_State_Score;
    for (int i = 0; i < Pmoves.size(); ++i) {
        int score;
        if(_DeepeningTable.find({state_id,Pmoves[i]})!=_DeepeningTable.end())
            score=_DeepeningTable[{state_id,Pmoves[i]}];
        else
        {
            if(IsMax)
                score=-oo;
            else
                score= oo;

        }
        Pmoves_State_Score.push_back({Pmoves[i],score});

    }
    if(IsMax)sort(Pmoves_State_Score.begin(),Pmoves_State_Score.end(),_MySortFunMax);
    else sort(Pmoves_State_Score.begin(),Pmoves_State_Score.end(),_MySortFunMin);
    Pmoves.clear();
    for (int j = 0; j < Pmoves_State_Score.size(); ++j) {
        Pmoves.push_back(Pmoves_State_Score[j].first);
    }
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
    clock_t tStart = clock();
    int firstguess = 0;
    for (int d = 1;d<=MaxDepth; d++) {
        RootBestMove=-1;
        RootBestScore=-oo;
        firstguess = this->_MTDF(root_id, firstguess, d);
    }
    pair<int,int> Bibi={firstguess,RootBestMove};
    _MTDfTable.clear();
    _DeepeningTable.clear();
    cout<<"EvalStates : ["<<EvalStates<<","<<OpenedStates<<"] in "<<clock() - tStart-Eval.TreeCreationTime<<" ms"<<endl;

    return Bibi;
}
int MTDF::_MTDF(int root_id, int f, int d)
{
    int g = f;
    int lowerbound = -oo;
    int upperbound = +oo;
    this->_MTDfTable.clear();
    while (lowerbound < upperbound) {
        int beta = (g == lowerbound) ? g + 1 : g;
        g = this->_AlphaBetaWithMemory(root_id, beta - 1, beta, d,true,d, true);
        if (g < beta) {
            upperbound = g;
        } else {
            lowerbound = g;
        }
    }
    return g;
}
int MTDF::_AlphaBetaWithMemory(int state_id, int alpha, int beta,int d,bool IsMax,int MaxDepth,bool DoNull) {


    Node entry;
    OpenedStates++;
    int g,_g,a,b;
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

    if (d == 0 || Search::Eval.IsGameFinished() || Search::Eval.hasTime() == false) {
        /* leaf node */
        if(_MTDfTable[state_id].value!=-oo)
            g=_MTDfTable[state_id].value;
        else
        {
            EvalStates++;
            g = Search::Qsearch(state_id,alpha,beta,IsMax);
        }
        this->_UpdateNode(state_id,g,alpha,beta);
        return g;
    }

    vector<int>Pmoves=this->_GetSortedPossibleMoves(state_id,IsMax);
    if(IsMax)
    {
        /*if(d>=3&&DoNull)
        {
            int NullSCore=_AlphaBetaWithMemory(state_id, alpha, beta, d-3,!IsMax,MaxDepth,false);
            if(NullSCore>=beta)
                return NullSCore;
        }*/

        g = -oo;
        a = alpha;
        for (int i = 0; (i < Pmoves.size())&&(g<beta); ++i) {
            _g=_AlphaBetaWithMemory(Pmoves[i], a, beta, d-1,!IsMax,MaxDepth,true);
            if(_g>RootBestScore&&state_id==1)
            {
                RootBestScore=_g;
                RootBestMove=Pmoves[i];
            }
            //_DeepeningTable[{state_id,Pmoves[i]}]=_g;
            g = max(g,_g);
            a = max(a,g);
        }
    } else
    {
        g = +oo;
        b = beta;
        for (int i = 0; (i < Pmoves.size())&&(g>alpha); ++i) {
            _g=_AlphaBetaWithMemory(Pmoves[i], alpha, b, d-1,!IsMax,MaxDepth,true);
            //_DeepeningTable[{state_id,Pmoves[i]}]=_g;
            g = min(g,_g);
            b = min(b,g);
        }
    }


    this->_UpdateNode(state_id,g,alpha,beta);
    return g;
}