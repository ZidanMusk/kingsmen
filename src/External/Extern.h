#ifndef MTD_F_EXTERN_H
#define MTD_F_EXTERN_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Extern {
public:
    int GetScore(int state_id);
    vector<int> GetPossibleMoves(int state_id);
    vector<int> GetCapturingMoves(int state_id);
    bool hasTime();
    bool IsGameFinished();
};


#endif //MTD_F_EXTERN_H
