#include <bits/stdc++.h>
#include "Search.h"

using namespace std;

#include "AlphaBeta.h"
#include "MTDF.h"
#include "PVS.h"

int main() {

    int maxDepth = 10;
    int timeL=30;

    /*Board* boardPvs = new Board();
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

     new MTDF(maxDepth,b1,e1, true, true, true,timeL);
*/
//Evaluate

    Board* b1 = new Board(false);
    b1->fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", false);
    Evaluate* e1 = new Evaluate(b1);
    Search *mtdf1 = new PVS(3,b1,e1,true,timeL);

    Board* b2 = new Board(false);
    b2->fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true);
    Evaluate* e2 = new Evaluate(b2);
    Search *mtdf2 = new PVS(10,b2,e2,true,timeL);

    vector<string> p1, p2;

    int counter = 0;

    while(!b1->isOver() && !b2->isOver()){
        p1.clear(); p2.clear();
        for (int i = 0; i < b1->allValidMoves.size(); i++){
            p1.push_back(b1->moveInterpret(b1->allValidMoves[i]));
        }
        for (int i = 0; i < b2->allValidMoves.size(); i++){
            p2.push_back(b2->moveInterpret(b2->allValidMoves[i]));
        }
        cout<<"=================================================="<<endl;
        cout<<"not matching moves in white palyer["<<b1->me<<"]: "<<endl;

        for (int i = 0; i < p1.size(); i++){
            bool x = true;
            for (int j = 0; j < p2.size(); j++){
                if(p1[i] == p2[j])x = false;
            }
            if(x){
                cout<<p1[i]<<endl;
            }
        }

        cout<<"not matching moves in black palyer["<<b2->me<<"]: "<<endl;

        for (int i = 0; i < p2.size(); i++){
            bool x = true;
            for (int j = 0; j < p1.size(); j++){
                if(p2[i] == p1[j])x = false;
            }
            if(x){
                cout<<p2[i]<<endl;
            }
        }
        if(b1->whiteToMove && !b2->whiteToMove){
            mtdf1->GetBestMove();
            int move = mtdf1->bestMove;
            string str = b1->moveInterpret(move);
            if(b1->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            if(b2->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            cout<<"done move: "<<str<<endl;
        }else if(!b1->whiteToMove && b2->whiteToMove){
            mtdf2->GetBestMove();
            int move = mtdf2->bestMove;
            string str = b2->moveInterpret(move);
            if(b1->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            if(b2->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            cout<<"done move: "<<str<<endl;

        }else{
            cout<<"mismatching turns\n";
            break;
        }

        if(b1->toFen() != b2->toFen()){
            cout<<"mismatching state\n";
            break;
        }
        if(++counter == 500)break;
        cout<<counter<<" moves done.\n";
        cout<<"new state: "<<b1->toFen()<<endl;
    }
    cout<<"white palyer["<<b1->me<<"]: "<<b1->gui_gameState()<<endl;
    cout<<"black palyer["<<b2->me<<"]: "<<b2->gui_gameState()<<endl;


}

