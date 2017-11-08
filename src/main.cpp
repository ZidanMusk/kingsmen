#include "Board.cpp"

int main() {
    Board b;
    b.fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/NRBQKBNR b KQkq - 1 2");
    b.allValidMoves = b.generateAllMoves();

    b.disp();
    cout<<endl<<__builtin_popcountll(b.whiteKnights)<<endl;

    b.doo(b.allValidMoves[0]);
    //b.doo(b.makeMoveMask(b.ENPASSANT, 0, b.pawnTypeNum(), 49, 49-16, 1));
    //cout<<endl<<(b.allValidMoves.size())<<endl;

    b.disp();

    return 0;
}