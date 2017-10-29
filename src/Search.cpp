#include "Search.h"

Search::Search(int maxDepth)
{this->_MaxDepth=maxDepth;}
pair<int,int> Search::GetBestMove(int state_id) {return this->_IterativeDeepening(state_id,this->_MaxDepth);}