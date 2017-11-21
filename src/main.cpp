#include "Board.cpp"

int main() {
    Board b;
    b.fenInterpreter("rnbqkbnr/1ppppppp/p7/8/PPPPPPPP/8/8/RNBQKBNR b KQkq - 1 2");

    b.doo(b.allValidMoves[25]);
    cout<<(b.allValidMoves).size()<<endl;
    b.doo(b.allValidMoves[0]);

    b.disp();


    return 0;
}