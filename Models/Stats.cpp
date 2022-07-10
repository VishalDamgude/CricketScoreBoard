#ifndef _Player_Stat_
#define _Player_Stat_

#include <string>
#include <vector>
#include <queue>
#include <memory>
#include "Player.cpp"
using namespace std;

class PlayerStat
{

public:
    shared_ptr<Player> player;
    int matchId = 0;
    PlayerStat(shared_ptr<Player> p, int id) : player(p), matchId(id)
    {
    }

    ~PlayerStat() {}
};

class BattingStat : public PlayerStat
{

public:
    int score = 0;
    int fours = 0;
    int sixes = 0;
    int balls = 0;
    double strikeRate = 0.0;

    BattingStat(shared_ptr<Player> p, int matchId) : PlayerStat(p, matchId)
    {
    }

    ~BattingStat()
    {
    }
};

class BowlingStat : public PlayerStat
{

public:
    double overs = 0.0;
    int runsConceded = 0;
    int wickets = 0;
    int maidenOvers = 0;
    double economy = 0.0;

    BowlingStat(shared_ptr<Player> p, int matchId) : PlayerStat(p, matchId)
    {
        // overs = 0.0;
    }
    ~BowlingStat() {}
};

#endif