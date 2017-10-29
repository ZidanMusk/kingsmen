#include "Board.cpp"

int main() {
    Board b;
    b.fenInterpreter("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");

    b.disp();
    b.whitePawnVMGen();
    cout<<endl<<__builtin_popcountll(b.whiteKnights)<<endl;

    b.doo(b.whiteKnightVMGen()[3]);
    cout<<endl<<__builtin_popcountll(b.whiteKnights)<<endl;

    b.disp();

    return 0;
}