#include "Board.cpp"

int main() {
    Board b;
    b.fenInterpreter("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", true);
    b.gui_isValid("e2", "e4", 0);

    b.gui_isValid("g8", "f6", 0);

    b.gui_isValid("a2", "a3", 0);

    b.gui_isValid("f6", "e4", 0);

    b.gui_isValid("d2", "d3", 0);

    b.gui_isValid("a7", "a6", 0);

    b.gui_isValid("c1", "g5", 0);

    b.gui_isValid("a6", "a5", 0);

    b.gui_isValid("g5", "e7", 0);

    b.gui_isValid("f8", "e7", 0);

    b.gui_isValid("h2", "h3", 0);

    b.gui_isValid("e7", "f8", 0);


    b.gui_isValid("d1", "e2", 0);


    b.gui_isValid("e4", "c5", 0);

    b.disp();


    return 0;
}