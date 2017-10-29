#include <iostream>
#include "Search.h"
#include "MTDF.h"
#include "PVS.h"

int main() {
    Search *Manga=new MTDF(4);
    Search *Bibo=new PVS(4);
    cout<<"MTDF Algorithm"<<endl;
    pair<int,int>Best=Manga->GetBestMove(1);
    cout<<"Best Score = "<<Best.first<<", Best Move State = "<<Best.second<<endl;
    cout<<"PVS Algorithm"<<endl;
    Best=Bibo->GetBestMove(1);
    cout<<"Best Score = "<<Best.first<<", Best Move State = "<<Best.second<<endl;

}

