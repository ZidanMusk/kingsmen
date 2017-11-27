#include "Board.cpp"

int main() {
    Board b;
    b.fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1", 'w');
    b.gui_isValid("b8", "a6", 0);
    cout<<b.gui_getPieceAt("a8")<<endl;
    //b.gui_isValid("b7", "b6", 0);
    //b.gui_isValid("c2", "c4", 0);
    //b.gui_isValid("g8", "h6", 0);
    //b.gui_isValid("d1", "b3", 0);
    /*b.doo(b.allValidMoves[49]);
    b.doo(b.allValidMoves[2]);
    b.doo(b.allValidMoves[6]);
    b.doo(b.allValidMoves[16]);
    cout<<b.isCheck()<<endl;
    cout<<b.allValidMoves.size()<<endl;

    b.doo(b.allValidMoves[0]);
*/
    b.disp();


    return 0;
}