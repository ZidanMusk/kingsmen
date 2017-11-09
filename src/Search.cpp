#include "Search.h"

Search::Search(int maxDepth)
{this->_MaxDepth=maxDepth;}
pair<int,int> Search::GetBestMove(int state_id) {return this->_IterativeDeepening(state_id,this->_MaxDepth);}
int Search::Qsearch(int state_id,int alpha, int beta,bool isMax) {
    int score=this->Eval.GetScore(state_id);
    if(isMax)
    {
        if(score>=beta)
            return score;
        alpha=max(alpha,score);
        vector<int>capturingMoves=this->Eval.GetCapturingMoves(state_id);
        for (int i = 0; i < (capturingMoves.size())&&score<beta; ++i) {
            score=max(score,Qsearch(capturingMoves[i],alpha,beta,!isMax));
            alpha=max(score,alpha);
        }
        return score;
    }
    else
    {
        if(score<=  alpha)
            return score;
        beta=min(beta,score);
        vector<int>capturingMoves=this->Eval.GetCapturingMoves(state_id);
        for (int i = 0; i < (capturingMoves.size())&&score>alpha; ++i) {
            score=min(score,Qsearch(capturingMoves[i],alpha,beta,!isMax));
            beta=min(score,beta);
        }
        return score;
    }

}