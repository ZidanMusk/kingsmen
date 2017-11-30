#include "Extern.h"

int Extern::GetScore(int state_id)
{
    ifstream file("../src/External/TreeRand.txt");
    string str;
    while (getline(file, str))
    {
        string delimiter = " ",token;
        size_t pos = 0;
        vector<int> fields;
        while ((pos = str.find(delimiter)) != string::npos) {
            token = str.substr(0, pos);
            fields.push_back(atoi(token.c_str()));
            str.erase(0, pos + delimiter.length());
        }
        fields.push_back(atoi(str.c_str()));
        if(fields[0]==state_id)
            return fields[1];
    }
    //return rand() % 19 + (-9);
}
vector<int> Extern::GetPossibleMoves(int state_id) {
    ifstream file("../src/External/TreeRand.txt");
    string str;
    vector<int> res;
    while (getline(file, str))
    {
        string delimiter = " ",token;
        size_t pos = 0;
        vector<int> fields;
        while ((pos = str.find(delimiter)) != string::npos) {
            token = str.substr(0, pos);
            fields.push_back(atoi(token.c_str()));
            str.erase(0, pos + delimiter.length());
        }
        fields.push_back(atoi(str.c_str()));
        if(fields[0]==state_id) {
            for (int i = 2; i < fields.size(); i++)
                res.push_back(fields[i]);
            return res;
        }
    }
}
vector<int> Extern::GetCapturingMoves(int state_id) {
   vector<int>R;
   return R;
}

bool Extern::hasTime() {return true;}
bool Extern::IsGameFinished() {return false;}