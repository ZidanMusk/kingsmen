#include <iostream>
#include "Search.h"
#include "External/ExternBig.h"
#include "MTDF.h"
#include "PVS.h"
#include "AlphaBeta.h"


#include <cassert>

unordered_map<ll,ll> ExternBig::SaveGetScore;
unordered_map<ll,vector<ll>> ExternBig::SaveGetPossibleMoves;

int main() {
    ll mtdfBest1 =0, mtdfBest2=0, mtfdCorrect =0;
    ll PvsBest1=0, PvsBest2=0, PvsCorrect =0;
    bool pvsSa7 = false;
    bool mtdfSa7 = false;
    ll trials = 1;
    ll MaxDepth = 7;
    for(ll i=0;i<trials;i++) {

        pvsSa7 = false;
        mtdfSa7 = false;
        cout << "Start Generating Tree of Depth = " << MaxDepth << endl;
        ExternBig::GenerateRandTree(1, 0, MaxDepth);
        cout << "END Generating The Tree" << endl;
        Search *Baseline = new AlphaBeta(MaxDepth);
        Baseline->GetBestMove(1);
        Search *Bibo = new PVS(MaxDepth, true);
        Bibo->GetBestMove(1);
        Search *Manga = new MTDF(MaxDepth, true, true);
        Manga->GetBestMove(1);
        if (Baseline->bestScore == Bibo->bestScore) {
            PvsCorrect += 1;
            pvsSa7 = true;
        }
        if (Baseline->bestScore == Manga->bestScore) {
            mtfdCorrect += 1;
            mtdfSa7 = true;
        }
        if(pvsSa7 && mtdfSa7){
            if(Bibo->uniqueCalls > Manga->uniqueCalls) mtdfBest1 +=1;
            if(Bibo->uniqueCalls < Manga->uniqueCalls) PvsBest1 +=1;
            if(Bibo->allCalls > Manga->allCalls) mtdfBest2 +=1;
            if(Bibo->allCalls < Manga->allCalls) PvsBest2 +=1;
        }
    }
    cout<<endl<<"============="<<endl;
    cout<<"PVS  correctness: "<<PvsCorrect <<"/"<<trials<<endl;
    cout<<"MTDF correctness: "<<mtfdCorrect <<"/"<<trials<<endl;
    cout<<endl<<"============="<<endl;
    cout<<"PVS  1st no. best: "<<PvsBest1 <<"/"<<trials<<endl;
    cout<<"MTDF 1st no. best: "<<mtdfBest1 <<"/"<<trials<<endl;
    cout<<endl<<"============="<<endl;
    cout<<"PVS  2nd no. best: "<<PvsBest2 <<"/"<<trials<<endl;
    cout<<"MTDF 2nd no. best: "<<mtdfBest2 <<"/"<<trials<<endl;
}

