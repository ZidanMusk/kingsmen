#include "Board.cpp"

int main() {
    Board b;
    b.fenInterpreter("rnbqkbnr//8/8/8/8/8/RNBQKBNR b KQkq - 1 2");
    b.doo(b.allValidMoves[2]);
    b.doo(b.allValidMoves[49]);
    b.doo(b.allValidMoves[2]);
    b.doo(b.allValidMoves[6]);
    b.doo(b.allValidMoves[40]);
    cout<<b.isCheck()<<endl;
    cout<<b.allValidMoves.size()<<endl;

    b.doo(b.allValidMoves[0]);

    b.disp();


    return 0;
}