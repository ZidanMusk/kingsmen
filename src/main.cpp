#include <bits/stdc++.h>
#include "Search.h"
#include "AlphaBeta.h"
#include "MTDF.h"
#include "PVS.h"

int main() {


    //TODO last board update changes search results
    //TODO check if states are unique
    int maxDepth = 6;
    Board* board1 = new Board();
    board1->fenInterpreter();
    Evaluate* evaluate1 = new Evaluate(board1);

    Board* board2 = new Board();
    board2->fenInterpreter();
    Evaluate* evaluate2 = new Evaluate(board2);

    //Search* baseline = new AlphaBeta(maxDepth,board1,evaluate1);
    //baseline->GetBestMove();

    Search *mtdf = new MTDF(maxDepth,board1,evaluate1, false, true);
    mtdf->GetBestMove();


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
 /*
    Board b;
    b.fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true);

    int x = 5;
    int moves[5] = {255872, 817536, 173696, 107088, 197632};
    for (int i = 0; i < x; ++i){
        bool d = false;
        for(int j = 0; j < b.allValidMoves.size(); ++j){
            if(b.allValidMoves[j] == moves[i]){
                cout<<"move: "<<moves[i]<<" done. "<<endl;
                d = true;
                b.doo(moves[i]);
            }
        }
        if(!d){
            cout<<"move: "<<moves[i]<<" doesn't exist. "<<endl;
            break;
        }
    }

    b.disp();
*/
}

