#ifndef _Over_
#define _Over_

#include <vector>
#include <string>
#include <memory>
#include "Player.cpp"
#include "Utils.h"

class Ball;
class Run;
class Wicket;

class Over
{
public:
    vector<Ball *> balls;
    int overNumber = 0;
    int fairDeliveries = 0;
    shared_ptr<Player> bowler;
    int runs = 0;
    int wickets = 0;
    Over(int number, shared_ptr<Player> bowler) : overNumber(number), bowler(bowler) {}
    void AddBall(Ball *b)
    {
        balls.push_back(b);
    };

    ~Over() {}
};

class Ball
{
public:
    shared_ptr<Player> batsman;
    BallType ballType;

    Wicket *wicket;
    vector<Run *> runs;

    Ball(shared_ptr<Player> b)
    {
        batsman = b;
        ballType = FAIR_DELIVERY;
    }

    ~Ball() {}
};

class Run
{
public:
    int totalRuns = 0;
    RunType runType;

    Run(int runs)
    {
        totalRuns = runs;
    }
};

class Wicket
{
public:
    WicketType wktType;
    Wicket()
    {
        wktType = BOWLED;
    }

    ~Wicket() {}
};

#endif