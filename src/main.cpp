#include <iostream>
#include "Search.h"
#include "External/ExternBig.h"
#include "MTDF.h"
#include "PVS.h"
#include "AlphaBeta.h"

int ExternBig::stateIDs=2;
unordered_map<int,int> ExternBig::SaveGetScore;
unordered_map<int,vector<int>> ExternBig::SaveGetPossibleMoves;

int main() {

    int MaxDepth=5;
    Search *Baseline=new AlphaBeta(MaxDepth);
    Search *Manga=new MTDF(MaxDepth);
    Search *Bibo=new PVS(MaxDepth);
    cout<<"AlphaBeta Baseline Algorithm"<<endl;
    pair<int,int>Bestx=Baseline->GetBestMove(1);
    cout<<"Best Score = "<<Bestx.first<<", Best Move State = "<<Bestx.second<<endl;
    cout<<"MTDF Algorithm"<<endl;
    pair<int,int>Best=Manga->GetBestMove(1);
    cout<<"Best Score = "<<Best.first<<", Best Move State = "<<Best.second<<endl;
    cout<<"PVS Algorithm"<<endl;
    Best=Bibo->GetBestMove(1);
    cout<<"Best Score = "<<Best.first<<", Best Move State = "<<Best.second<<endl;

}

