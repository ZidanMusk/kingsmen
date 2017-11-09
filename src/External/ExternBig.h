//
// Created by mangawy on 11/7/17.
//

#ifndef KINGSMEN_EXTERNBIG_H
#define KINGSMEN_EXTERNBIG_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <vector>
using namespace std;

class ExternBig {
public:
    static unordered_map<int,int>SaveGetScore;
    static unordered_map<int,vector<int>>SaveGetPossibleMoves;
    static int stateIDs;
    int TreeCreationTime=0;
    int GetScore(int state_id);
    vector<int> GetPossibleMoves(int state_id);
    vector<int> GetCapturingMoves(int state_id);
    bool hasTime();
    bool IsGameFinished();

};


#endif //KINGSMEN_EXTERNBIG_H
