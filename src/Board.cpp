class Board {


public:

    unsigned long long whitePawns;
    unsigned long long whiteKnights;
    unsigned long long whiteBishops;
    unsigned long long whiteRooks;
    unsigned long long whiteQueens;
    unsigned long long whiteKing;

    unsigned long long blackPawns;
    unsigned long long blackKnights;
    unsigned long long blackBishops;
    unsigned long long blackRooks;
    unsigned long long blackQueens;
    unsigned long long blackKing;

    unsigned long long whitePieces;
    unsigned long long blackPieces;
    unsigned long long allPieces;

    unsigned long long key; // zobrist key

    void pass(){}
    void doo(){}
    void undoo(){}
    void isEndGame(){}
    void isDraw(){}
    void isMate(){}
    void check(){}





};