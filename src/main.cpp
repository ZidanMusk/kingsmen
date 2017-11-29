#include <bits/stdc++.h>
#include "Search.h"
#include "AlphaBeta.h"
#include "MTDF.h"
#include "PVS.h"

int main() {

    //TODO last board update changes search results
    //TODO check if states are unique
    int maxDepth = 6;
    Board* board = new Board();
    board->fenInterpreter();
    Evaluate* evaluate = new Evaluate(board);
    //Search* baseline = new AlphaBeta(maxDepth,board,evaluate);
    //baseline->GetBestMove();


    //cout<<"###################"<<endl;
    Search *mtdf = new MTDF(maxDepth,board,evaluate, false, false);
    mtdf->GetBestMove();

    Search *mtdfNull = new MTDF(maxDepth,board,evaluate, true, false);
    mtdfNull->GetBestMove();


    //cout<<"###################"<<endl;
    //Search *pvs = new PVS(maxDepth,board,evaluate, false);
    //pvs->GetBestMove();

    //Search *pvsnull = new PVS(maxDepth,board,evaluate, true);
    //pvsnull->GetBestMove();



    /*ll mtdfBest1 = 0, mtdfBest2 = 0, mtfdCorrect = 0;
    ll PvsBest1 = 0, PvsBest2 = 0, PvsCorrect = 0;
    bool pvsSa7 = false;
    bool mtdfSa7 = false;
    ll trials = 1;
    ll MaxDepth = 7;
    for (ll i = 0; i < trials; i++) {

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
        if (pvsSa7 && mtdfSa7) {
            if (Bibo->uniqueCalls > Manga->uniqueCalls) mtdfBest1 += 1;
            if (Bibo->uniqueCalls < Manga->uniqueCalls) PvsBest1 += 1;
            if (Bibo->allCalls > Manga->allCalls) mtdfBest2 += 1;
            if (Bibo->allCalls < Manga->allCalls) PvsBest2 += 1;
        }
    }
    cout << endl << "=============" << endl;
    cout << "PVS  correctness: " << PvsCorrect << "/" << trials << endl;
    cout << "MTDF correctness: " << mtfdCorrect << "/" << trials << endl;
    cout << endl << "=============" << endl;
    cout << "PVS  1st no. best: " << PvsBest1 << "/" << trials << endl;
    cout << "MTDF 1st no. best: " << mtdfBest1 << "/" << trials << endl;
    cout << endl << "=============" << endl;
    cout << "PVS  2nd no. best: " << PvsBest2 << "/" << trials << endl;
    cout << "MTDF 2nd no. best: " << mtdfBest2 << "/" << trials << endl;


*/


//Evaluate
//    Board b;
//    b.fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true);
//    b.gui_isValid("f2", "f4", 0);
//
//    b.gui_isValid("e7", "e5", 0);
//
//    b.gui_isValid("a2", "a3", 0);
//
//    b.gui_isValid("e5", "f4", 0);
//
//    b.gui_isValid("h2", "h4", 0);
//
//    b.gui_isValid("a7", "a6", 0);
//
//    b.gui_isValid("h1", "h3", 0);
//
//    b.gui_isValid("h7", "h6", 0);
//
//    b.gui_isValid("h3", "e3", 0);
//
//    cout<<b.gui_isValid("f7", "f5", 0)<<endl;
//    cout<<b.gui_gameState()<<endl;
//    b.disp();

}

