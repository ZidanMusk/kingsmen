#include <bits/stdc++.h>
#include "Search.h"

using namespace std;

#include "AlphaBeta.h"
#include "MTDF.h"
#include "PVS.h"

int main() {

    /*  int maxDepth = 6;
      Board* board1 = new Board();
      board1->fenInterpreter();
      Evaluate* evaluate1 = new Evaluate(board1);

      Board* board2 = new Board();
      board2->fenInterpreter();
      Evaluate* evaluate2 = new Evaluate(board2);

      Search *pvs = new PVS(maxDepth,board1,evaluate1, true);
      pvs->GetBestMove();
      //Search* baseline = new AlphaBeta(maxDepth,board1,evaluate1);
      //baseline->GetBestMove();

      //Search *mtdf = new MTDF(maxDepth,board1,evaluate1, false, true);
      //mtdf->GetBestMove();



      exit(0);
      /*for(int i=0;i<10;i++)
      {
          mtdf->GetBestMove();
          board1->doo(mtdf->bestMove);
          mtdfNull->GetBestMove();
          board2->doo(mtdfNull->bestMove);
      }*/


    /*cout<<board->key<<endl;
    int arr[] ={205952,891392,230912,824832,843200};
    for(int j=0;j<5;++j){

        cout<<"State Id : "<<board->key<<", Move : "<<arr[j];
        for(int i=0;i<board->allValidMoves.size();i++)
        {
            if(arr[j] == board->allValidMoves[i])
                cout<<" and move is correct";

        }
        cout<<endl;
        board->doo(arr[j]);

    }*/
    /*board->doo(205952);
    cout<<board->key<<endl;
    board->doo(891392);
    cout<<board->key<<endl;
    board->doo(230912);
    cout<<board->key<<endl;
    board->doo(824832);
    cout<<board->key<<endl;
    board->doo(843200);
    cout<<board->key<<endl;
*/








    //Search* baseline = new AlphaBeta(maxDepth,board,evaluate);
    //baseline->GetBestMove();


    //cout<<"###################"<<endl;
    //Search *mtdf = new MTDF(maxDepth,board,evaluate, false, false);
    //mtdf->GetBestMove();

    /*Search *mtdfNull = new MTDF(maxDepth,board,evaluate, true, false);
    mtdfNull->GetBestMove();*/


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

    Board b;
    b.fenInterpreter("c2b20dr2r4/4bp1p/1p1k3P/pP1q4/P7/8/1K6/6q1 w KQkq - 0 1", true);

    cout<<b.isOver()<<endl;
    b.doo(255872);
    cout<<b.isOver()<<endl;
    b.doo(825856);
    cout<<b.isOver()<<endl;
    b.doo(323456);
    cout<<b.isOver()<<endl;
    b.doo(843200);
    cout<<b.isOver()<<endl;
    b.doo(239232);
    cout<<b.isOver()<<endl;
    b.doo(709440);
    cout<<b.isOver()<<endl;
    cout<<b.gui_gameState()<<endl;

    /*b.gui_isValid("a2", "a3", 0);
    b.gui_isValid("g8", "f6", 0);
    b.gui_isValid("c2", "c4", 0);
    b.gui_isValid("d7", "d5", 0);
    b.gui_isValid("g1", "f3", 0);
    b.gui_isValid("e7", "e6", 0);
    b.gui_isValid("d2", "d4", 0);
    b.gui_isValid("c7", "c5", 0);
    b.gui_isValid("e2", "e3", 0);
    b.gui_isValid("b8", "c6", 0);
    b.gui_isValid("b1", "c3", 0);
    b.gui_isValid("f8", "e7", 0);
    b.gui_isValid("d4", "c5", 0);
    b.gui_isValid("e7", "c5", 0);
    b.gui_isValid("h2", "h3", 0);
    b.gui_isValid("e8", "g8", 0);
    b.gui_isValid("c1", "d2", 0);
    b.gui_isValid("c6", "a5", 0);
    b.gui_isValid("c4", "d5", 0);
    b.gui_isValid("e6", "d5", 0);
    b.gui_isValid("b2", "b4", 0);
    b.gui_isValid("c5", "b4", 0);
    b.gui_isValid("a3", "b4", 0);
    b.gui_isValid("a5", "c6", 0);
    b.gui_isValid("d1", "b1", 0);
    b.gui_isValid("g7", "g6", 0);
    b.gui_isValid("f1", "d3", 0);
    b.gui_isValid("c8", "f5", 0);
    b.gui_isValid("d3", "f5", 0);
    b.gui_isValid("g6", "f5", 0);
    b.gui_isValid("b1", "f5", 0);
    b.gui_isValid("c6", "b4", 0);
    b.gui_isValid("e1", "g1", 0);
    b.gui_isValid("d8", "c8", 0);
    b.gui_isValid("f5", "g5", 0);
    b.gui_isValid("g8", "h8", 0);
    b.gui_isValid("g5", "f6", 0);
    b.gui_isValid("h8", "g8", 0);
    b.gui_isValid("f6", "h6", 0);
    b.gui_isValid("g8", "h8", 0);
    b.gui_isValid("f3", "g5", 0);
    b.gui_isValid("c8", "f5", 0);
    b.gui_isValid("a1", "a7", 0);
    b.gui_isValid("f8", "g8", 0);
    b.gui_isValid("e3", "e4", 0);
    b.gui_isValid("f5", "g5", 0);
    b.gui_isValid("d2", "g5", 0);
    b.gui_isValid("g8", "g5", 0);
    b.gui_isValid("h6", "f6", 0);
    b.gui_isValid("h8", "g8", 0);
    b.gui_isValid("a7", "a8", 0);

    cout << b.gui_gameState() << endl;

//    int x = 5;
//    int moves[5] = {255872, 817536, 173696, 107088, 197632};
//    for (int i = 0; i < x; ++i){
//        bool d = false;
//        for(int j = 0; j < b.allValidMoves.size(); ++j){
//            if(b.allValidMoves[j] == moves[i]){
//                cout<<"move: "<<moves[i]<<" done. "<<endl;
//                d = true;
//                b.doo(moves[i]);
//            }
//        }
//        if(!d){
//            cout<<"move: "<<moves[i]<<" doesn't exist. "<<endl;
//            break;
//        }
//    }
*/

    b.disp();
}

