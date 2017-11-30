#include <bits/stdc++.h>
#include "Search.h"

using namespace std;

#include "AlphaBeta.h"
#include "MTDF.h"
#include "PVS.h"

int main() {
/*
    int maxDepth = 10;
    int timeL=30;

    Board* boardPvs = new Board();
    boardPvs->fenInterpreter();
    Evaluate* evaluatePvs = new Evaluate(boardPvs);

    Board* boardMtdf = new Board(false);
    boardMtdf->fenInterpreter();
    Evaluate* evaluateMtdf = new Evaluate(boardMtdf);


    //Search* baseline = new AlphaBeta(maxDepth,board,evaluate);
    //baseline->GetBestMove();
    Search *pvs = new PVS(maxDepth,boardPvs,evaluatePvs,true,timeL);
    pvs->GetBestMove();
    Search *mtdf = new MTDF(maxDepth,boardMtdf,evaluateMtdf, true, true, true,timeL);
    mtdf->GetBestMove();

*/
    /*for (int i = 0; i < size; ++i) {
           cout<<"state 0: "<<board->key<<endl;
           vector<int> vv = board->allValidMoves;
           for (int j = 0; j < vv.size(); ++j) {
               if(arr[i] == vv[j]){cout<<"VALID!\n";}
           }
           board->doo(arr[i]);
           cout<<"state 1: "<<board->key<<endl;
           cout<<board->isOver()<<endl;
           board->undoo();
           cout<<endl;

       }*/
    /*board2->doo(255872);
    cout<<board2->key<<endl;
    cout<<"is it Over: "<<board2->isOver()<<endl;
*/
//8335008165548075498


    ////Search *pvs = new PVS(maxDepth,board1,evaluate1, true);
    //pvs->GetBestMove();
    /*  Search* baseline = new AlphaBeta(maxDepth,board1,evaluate1);
      baseline->GetBestMove();
  */

    /*map <ll,int> xxx;
    cout<<"IsOver\n";
    for (int i = 0; i < mtdf->debugIsOver.size(); ++i) {
        if(xxx.find(mtdf->debugIsOver[i].first)== xxx.end()){
            cout<<mtdf->debugIsOver[i].first<<" "<<mtdf->debugIsOver[i].second<<endl;
            xxx[mtdf->debugIsOver[i].first] =1;
        }
    }
    map <ll,int> xxx2;
    cout<<"EmptyMoves\n";
    for (int i = 0; i < mtdf->debugEmptyMoves.size(); ++i) {
        if(xxx2.find(mtdf->debugEmptyMoves[i].first)== xxx2.end()){
            cout<<mtdf->debugEmptyMoves[i].first<<" "<<mtdf->debugEmptyMoves[i].second<<endl;
            xxx2[mtdf->debugEmptyMoves[i].first] =1;
        }
    }*/
    //MTDF      : [22,255872,57877,89461] in 9 sec
    //MTDF      : [22,255872,57902,92232] in 10 sec



    //exit(0);
    /*for(int i=0;i<15;i++)
    {
        pvs->GetBestMove();
        board1->doo(pvs->bestMove);
        //mtdf->GetBestMove();
        //board2->doo(mtdf->bestMove);
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
    b.fenInterpreter("B2q1r2/4b1p1/k2pbp2/1p5p/pP1PpB1P/7N/P1P1QPP1/R3R1K1 b - - 0 1", true);



    cout<<b.gui_isValid("a6", "h7", 0)<<endl;

    cout<<b.gui_gameState()<<endl;


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


    b.disp();

}

