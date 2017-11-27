//
// Created by mangawy on 11/7/17.
//

#include "ExternBig.h"


void ExternBig::GenerateRandTree(ll node,ll d,ll MaxDepth) {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);
    uniform_real_distribution<double> distribution (-5000.0,5000.0);
    SaveGetScore[node]=distribution(generator);
    if(d==MaxDepth)
        return;
    vector<ll>C;
    ll Cc=8;
    ll start=Cc*(node-1)+1,end=Cc*(node-1)+Cc;
    for(ll i=start+1;i<=end+1;i++)
    {
        //cout<<d<<" "<<node<<" "<<i<<endl;
        C.push_back(i);
        GenerateRandTree(i,d+1,MaxDepth);
    }
    SaveGetPossibleMoves[node]=C;
}
ll ExternBig::GetScore(ll state_id)
{
    return ExternBig::SaveGetScore[state_id];
}
vector<ll> ExternBig::GetPossibleMoves(ll state_id) {

    return ExternBig::SaveGetPossibleMoves[state_id];
}
vector<ll> ExternBig::GetCapturingMoves(ll state_id) {
    vector<ll>R;
    return R;
}

bool ExternBig::hasTime() {return true;}
bool ExternBig::IsGameFinished() {return false;}