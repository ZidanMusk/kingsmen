#include "Board.cpp"

int main() {
    Board b;
    b.fenInterpreter("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");

    b.disp();
    b.whitePawnVMGen();
    b.doo(b.whitePawnVM[1]);
    cout<<endl<<endl;
    b.disp();

    return 0;
}