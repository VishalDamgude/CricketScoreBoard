#ifndef _Inning_Score_
#define _Inning_Score_

#include <string>
#include <vector>
using namespace std;

class InningScore
{
public:
    int totalScore;
    int extras;
    int wides;
    int noBalls;
    int wickets;
    int fours;
    int sixes;

    InningScore()
    {
        totalScore = 0;
        extras = 0;
        wides = 0;
        noBalls = 0;
        wickets = 0;
        fours = 0;
        sixes = 0;
    }
};

#endif