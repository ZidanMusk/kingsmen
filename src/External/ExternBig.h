//
// Created by mangawy on 11/7/17.
//

#ifndef KINGSMEN_EXTERNBIG_H
#define KINGSMEN_EXTERNBIG_H

#define ll  long long

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

class ExternBig {
public:
    static unordered_map<ll,ll>SaveGetScore;
    static unordered_map<ll,vector<ll>>SaveGetPossibleMoves;
    ll TreeCreationTime=0;
    ll GetScore(ll state_id);
    vector<ll> GetPossibleMoves(ll state_id);
    vector<ll> GetCapturingMoves(ll state_id);
    bool hasTime();
    bool IsGameFinished();
    static void GenerateRandTree(ll node,ll d,ll MaxDepth);
    bool IsCheck(){return false;}
    void makeNullMove(ll state_id){return;}
};


#endif //KINGSMEN_EXTERNBIG_H
