#include <bits/stdc++.h>
#include "Search.h"
#include "Evaluate.h"
#include "AlphaBeta.h"
#include "PVS.h"
#include "MTDF.h"
#include "Controller.cpp"


int main(){

//    ifstream config_file;
//    config_file.open("config.txt");
//
//    string gui_port;
//    string agent_port;
//    string my_ip;
//    config_file >> gui_port >> agent_port >> my_ip;
//    config_file.close();
//
//    cout << gui_port << endl;
//    cout << agent_port << endl;
//    cout << my_ip << endl;
//    name comm = name(gui_port, agent_port, my_ip);
//    comm.run();



//    Board *board = new Board();
//
//    string str = "r2qkbr1/pbp3pp/1pn2p2/4p3/3Pp1nP/2N5/PPP2PP1/R1BQKBR1 b KQkq - 0 1";
//    Evaluate *evaluate = new Evaluate(board);
//
//    //string str = "r1bqkbr1/pNp3pp/1pn2p2/4p3/3Pp1nP/2N5/PPP2PP1/R1BQKBR1 b KQkq - 0 1";
//    board->fenInterpreter(str, 1);
//    cout << evaluate->evaluate()<<endl;
//    //board->gui_isValid("c8","b7",0);
//    cout << evaluate->evaluate()<<endl;



    int maxDepth = 10;
    int timeL = 25;



    Board* b1 = new Board();
    b1->fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", false);
    Evaluate* e1 = new Evaluate(b1);
    Search *mtdf1 = new PVS(6,b1,e1,true,timeL);
    Board* b2 = new Board();
    b2->fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true);
    Evaluate* e2 = new Evaluate(b2);
//    cout<<b1->gui_isValid("d2", "d4", 0)<<endl;
//    cout<<b1->gui_isValid("e7", "e6", 0)<<endl;
//    cout<<b1->gui_isValid("g1", "f3", 0)<<endl;
//    cout<<b1->gui_isValid("d7", "d5", 0)<<endl;
//    cout<<b1->gui_isValid("c1", "g5", 0)<<endl;
//    cout<<b1->gui_isValid("f7", "f6", 0)<<endl;
//    cout<<b1->gui_isValid("g5", "e3", 0)<<endl;
//    cout<<b1->gui_isValid("g8", "e7", 0)<<endl;
//    cout<<b1->gui_isValid("b1", "c3", 0)<<endl;
//    cout<<b1->gui_isValid("e7", "f5", 0)<<endl;
//    cout<<b1->gui_isValid("h1", "g1", 0)<<endl;
//    cout<<b1->gui_isValid("b8", "c6", 0)<<endl;
//    cout<<b1->gui_isValid("d1", "d2", 0)<<endl;
//    cout<<b1->gui_isValid("b7", "b6", 0)<<endl;
//    cout<<b1->gui_isValid("g2", "g4", 0)<<endl;
//    cout<<b1->gui_isValid("f5", "e7", 0)<<endl;
//    cout<<b1->gui_isValid("a1", "d1", 0)<<endl;
//    cout<<b1->gui_isValid("d8", "d6", 0)<<endl;
//    cout<<b1->gui_isValid("h2", "h3", 0)<<endl;
//    cout<<b1->gui_isValid("c8", "a6", 0)<<endl;
//    cout<<b1->gui_isValid("g4", "g5", 0)<<endl;
//    cout<<b1->gui_isValid("e8", "c8", 0)<<endl;
//    cout<<b1->gui_isValid("g5", "f6", 0)<<endl;
//    cout<<b1->gui_isValid("g7", "g6", 0)<<endl;
//    cout<<b1->gui_isValid("e3", "f4", 0)<<endl;
//    cout<<b1->gui_isValid("d6", "b4", 0)<<endl;
//    cout<<b1->gui_isValid("a2", "a3", 0)<<endl;
//    cout<<b1->gui_isValid("b4", "a5", 0)<<endl;
//    cout<<b1->gui_isValid("f6", "e7", 0)<<endl;
//    cout<<b1->gui_isValid("f8", "e7", 0)<<endl;
//    cout<<b1->gui_isValid("d2", "e3", 0)<<endl;
//    cout<<b1->gui_isValid("h8", "f8", 0)<<endl;
//    cout<<b1->gui_isValid("b2", "b4", 0)<<endl;
//    cout<<b1->gui_isValid("c6", "b4", 0)<<endl;
//    cout<<b1->gui_isValid("a3", "b4", 0)<<endl;
//    cout<<b1->gui_isValid("e7", "b4", 0)<<endl;
//    cout<<b1->gui_isValid("e3", "e6", 0)<<endl;
//    cout<<b1->gui_isValid("d8", "d7", 0)<<endl;
//    cout<<b1->gui_isValid("f4", "d6", 0)<<endl;
//    cout<<b1->gui_isValid("b4", "c3", 0)<<endl;
//
//    for(int i = 0; i < b1->allValidMoves.size(); i++)
//    {
//        cout<<b1->moveInterpret(b1->allValidMoves[i])<<endl;
//    }
//
//    b1->disp();

    int counter = 0;

    while(!b1->isOver()){
        if(b1->whiteToMove){
            mtdf1->GetBestMove();
            int move = mtdf1->bestMove;
            string str = b1->moveInterpret(move);
            if(b1->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            if(b2->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            cout<<"evaluation of p1: "<<e1->evaluate(true)<<endl;
            cout<<"evaluation of p2: "<<e2->evaluate(true)<<endl;
            cout<<"done move: "<<str<<endl;
        }else {
            string str;
            cin>>str;

            if(b1->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            if(b2->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
            cout<<"evaluation of p1: "<<e1->evaluate(true)<<endl;
            cout<<"evaluation of p2: "<<e2->evaluate(true)<<endl;
            cout<<"done move: "<<str<<endl;

        }
        cout<<b1->toFen()<<endl;
        b1->disp();

        if(++counter == 500)break;

    }
    cout<<"white palyer["<<b1->me<<"]: "<<b1->gui_gameState()<<endl;




//    Board* b1 = new Board();
//    b1->fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", false);
//    Evaluate* e1 = new Evaluate(b1);
//    Search *mtdf1 = new PVS(10,b1,e1,true,timeL);
//
//    Board* b2 = new Board();
//    b2->fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true);
//    Evaluate* e2 = new Evaluate(b2);
//    Search *mtdf2 = new MTDF(10,b2,e2,true,true,true,timeL);
//
//    vector<string> p1, p2;
//
//    int counter = 0;
//
//    while(!b1->isOver() && !b2->isOver()){
//        p1.clear(); p2.clear();
//        for (int i = 0; i < b1->allValidMoves.size(); i++){
//            p1.push_back(b1->moveInterpret(b1->allValidMoves[i]));
//        }
//        for (int i = 0; i < b2->allValidMoves.size(); i++){
//            p2.push_back(b2->moveInterpret(b2->allValidMoves[i]));
//        }
//        cout<<"=================================================="<<endl;
//        cout<<"not matching moves in white palyer["<<b1->me<<"]: "<<endl;
//
//        for (int i = 0; i < p1.size(); i++){
//            bool x = true;
//            for (int j = 0; j < p2.size(); j++){
//                if(p1[i] == p2[j])x = false;
//            }
//            if(x){
//                cout<<p1[i]<<endl;
//            }
//        }
//
//        cout<<"not matching moves in black palyer["<<b2->me<<"]: "<<endl;
//
//        for (int i = 0; i < p2.size(); i++){
//            bool x = true;
//            for (int j = 0; j < p1.size(); j++){
//                if(p2[i] == p1[j])x = false;
//            }
//            if(x){
//                cout<<p2[i]<<endl;
//            }
//        }
//        if(b1->whiteToMove && !b2->whiteToMove){
//            mtdf1->GetBestMove();
//            int move = mtdf1->bestMove;
//            string str = b1->moveInterpret(move);
//            if(b1->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
//            if(b2->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
//            cout<<"evaluation of p1: "<<e1->evaluate()<<endl;
//            cout<<"evaluation of p2: "<<e2->evaluate()<<endl;
//            cout<<"done move: "<<str<<endl;
//        }else if(!b1->whiteToMove && b2->whiteToMove){
//            mtdf2->GetBestMove();
//            int move = mtdf2->bestMove;
//            string str = b2->moveInterpret(move);
//            if(b1->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
//            if(b2->gui_isValid(str.substr(0, 2), str.substr(2, 2), str[4] - '0')!='V')cout<<"a7a"<<endl;
//            cout<<"evaluation of p1: "<<e1->evaluate()<<endl;
//            cout<<"evaluation of p2: "<<e2->evaluate()<<endl;
//            cout<<"done move: "<<str<<endl;
//
//        }else{
//            cout<<"mismatching turns\n";
//            break;
//        }
//
//        if(b1->toFen() != b2->toFen()){
//            cout<<"mismatching state\n";
//            break;
//        }
//        if(++counter == 500)break;
//        cout<<counter<<" moves done.\n";
//        cout<<"new state: "<<b1->toFen()<<endl;
//    }
//    cout<<"white palyer["<<b1->me<<"]: "<<b1->gui_gameState()<<endl;
//    cout<<"black palyer["<<b2->me<<"]: "<<b2->gui_gameState()<<endl;

    return 0;
}