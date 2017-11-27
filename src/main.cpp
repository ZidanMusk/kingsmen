#include <bits/stdc++.h>
#include "Search.h"
#include "AlphaBeta.h"

//unordered_map<ll, ll> ExternBig::SaveGetScore;
//unordered_map<ll, vector<ll>> ExternBig::SaveGetPossibleMoves;




int main() {
    int maxDepth = 0;
    Board* board = new Board();
    board->fenInterpreter();
    Evaluate* evaluate = new Evaluate(board);
    Search* baseline = new AlphaBeta(maxDepth,board,evaluate);
    baseline->GetBestMove();

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
//    b.fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1", 'w');
//    b.gui_isValid("b8", "a6", 0);
//    cout<<b.gui_getPieceAt("a8")<<endl;
//    //b.gui_isValid("b7", "b6", 0);
//    //b.gui_isValid("c2", "c4", 0);
//    //b.gui_isValid("g8", "h6", 0);
//    //b.gui_isValid("d1", "b3", 0);
//    /*b.doo(b.allValidMoves[49]);
//    b.doo(b.allValidMoves[2]);
//    b.doo(b.allValidMoves[6]);
//    b.doo(b.allValidMoves[16]);
//    cout<<b.isCheck()<<endl;
//    cout<<b.allValidMoves.size()<<endl;
//
//    b.doo(b.allValidMoves[0]);
//*/
//    b.disp();

}

