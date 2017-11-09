//
// Created by mangawy on 11/7/17.
//

#include "ExternBig.h"



int ExternBig::GetScore(int state_id)
{
    return ExternBig::SaveGetScore[state_id];
}
vector<int> ExternBig::GetPossibleMoves(int state_id) {
    clock_t tStart = clock();
    if(ExternBig::SaveGetPossibleMoves.find(state_id)==ExternBig::SaveGetPossibleMoves.end()) {
        vector<int>C;
        //cout<<"child of state "<<state_id<<" is : ";
        for (int j = 0; j < 15; ++j) {
            ExternBig::SaveGetScore[stateIDs]=rand() % 1000 + (-500);
            //cout<<"["<<stateIDs<<","<<ExternBig::SaveGetScore[stateIDs]<<"]";
            C.push_back(ExternBig::stateIDs++);
        }
        //cout<<endl;
        ExternBig::SaveGetPossibleMoves[state_id]=C;
    }
    //TreeCreationTime+=(clock()-tStart);
    return ExternBig::SaveGetPossibleMoves[state_id];
}
vector<int> ExternBig::GetCapturingMoves(int state_id) {
    vector<int>R;
    return R;
}

bool ExternBig::hasTime() {return true;}
bool ExternBig::IsGameFinished() {return false;}