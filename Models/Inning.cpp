#ifndef _Inning_
#define _Inning_

#include <string>
#include <vector>
#include <list>
#include <unordered_map>
#include <iostream>
#include <ctime>
#include <memory>
#include "Team.cpp"
#include "InningScore.cpp"
#include "Over.cpp"
#include "Stats.cpp"

using namespace std;

class Inning
{
public:
    int id;
    time_t startTime;
    time_t endTime;
    int totalOvers;
    vector<Over *> overs;
    shared_ptr<Team> battingTeam;
    shared_ptr<Team> bowlingTeam;
    vector<shared_ptr<Player>> bowlers;

    InningScore *inningScore;
    list<shared_ptr<Player>> battingOrder;
    InningStatus status;

    shared_ptr<Player> strikerEnd;
    shared_ptr<Player> nonStrikerEnd;

    map<string, shared_ptr<BattingStat>> battingStats;
    map<string, shared_ptr<BowlingStat>> bowlingStats;

public:
    Inning(int overs, int id)
    {
        id = id;
        inningScore = new InningScore();
        totalOvers = overs;
    }
    ~Inning()
    {
        delete inningScore;
    }
    void StartInning()
    {
        startTime = time(0);
        status = STARTED;
    }

    void SwitchEnds(shared_ptr<Player> p1, shared_ptr<Player> p2)
    {
        strikerEnd = p1;
        nonStrikerEnd = p2;
    }

    shared_ptr<BattingStat> GetBattingStats(string name)
    {
        return battingStats[name];
    }

    shared_ptr<BowlingStat> GetBowlingStats(string name)
    {
        return bowlingStats[name];
    }

    void InitializeBattingOrder(vector<string> &batOrder)
    {
        for (auto &name : batOrder)
        {
            auto p = battingTeam->GetPlayer(name);
            battingOrder.push_back(shared_ptr<Player>(p));
        }
        auto striker = battingOrder.front();
        strikerEnd = striker;
        battingOrder.pop_front();

        auto nonStriker = battingOrder.front();
        nonStrikerEnd = nonStriker;
        battingOrder.pop_front();
    }

    void InitializeBatsmanStats(int matchId)
    {
        battingStats.insert({strikerEnd->name, make_shared<BattingStat>(strikerEnd, matchId)});
        battingStats.insert({nonStrikerEnd->name, make_shared<BattingStat>(nonStrikerEnd, matchId)});

        for (auto it = battingOrder.begin(); it != battingOrder.end(); ++it)
        {
            auto p = *it;
            battingStats.insert({p->name, make_shared<BattingStat>(p, matchId)});
        }
    }
    void DisplayBattingScore()
    {
        cout << "Batting score for " << battingTeam->name << ":" << endl;
        printf("Batsman\t\t Score\t 4s\t 6s\t Balls\t Strike Rate\n");

        for (auto it : battingTeam->players)
        {
            shared_ptr<Player> p = it.second;
            printf("%s", it.first.c_str());
            if (p == strikerEnd || p == nonStrikerEnd)
            {
                printf("*");
            }
            shared_ptr<BattingStat> batsmanStat = GetBattingStats(p->name);
            if (batsmanStat)
            {
                printf("\t\t %d\t %d\t %d\t %d\t %.2f\n", batsmanStat->score, batsmanStat->fours, batsmanStat->sixes, batsmanStat->balls, batsmanStat->strikeRate);
            }
        }
        cout << endl;
        cout << "Total: " << inningScore->totalScore << "/" << inningScore->wickets << endl;
        cout << "Extras: " << inningScore->extras << "(WD " << inningScore->wides << ", NB " << inningScore->noBalls << ")" << endl;
        cout << "Overs: " << overs.size() << endl;
        cout << endl;
    }

    void DisplaBowlingStats()
    {

        cout << "Bowling stats for " << bowlingTeam->name << ":" << endl;
        printf("Bowler\t\t Overs\t M\t R\t W\t Economy\n");

        for (auto bowler : bowlers)
        {
            shared_ptr<BowlingStat> bowlerStat = GetBowlingStats(bowler->name);
            if (bowlerStat)
            {
                printf("%s\t\t %.1f\t %d\t %d\t %d\t %.2f\n", bowler->name.c_str(), bowlerStat->overs, bowlerStat->maidenOvers, bowlerStat->runsConceded, bowlerStat->wickets,
                       bowlerStat->economy);
            }
        }

        cout << endl;
    }
    void DisplayScoreBoard()
    {
        cout << "Scoreboard after over " << overs.size() << endl;
        DisplayBattingScore();
        DisplaBowlingStats();
    }

    void RecordOver(int matchId, vector<string> &overInfo, shared_ptr<Player> bowler, int overNumber)
    {
        shared_ptr<BowlingStat> bowlerStat;
        if (bowlingStats.find(bowler->name) == bowlingStats.end())
        {
            bowlerStat = make_shared<BowlingStat>(bowler, matchId);
            bowlingStats.insert({bowler->name, bowlerStat});
            bowlers.push_back(bowler);
        }
        else
        {
            bowlerStat = GetBowlingStats(bowler->name);
        }
        Over *over = new Over(overNumber, bowler);

        for (int i = 0; i < overInfo.size(); i++)
        {
            auto striker = strikerEnd;

            shared_ptr<BattingStat> batsmanStat = GetBattingStats(striker->name);

            Ball *ball = new Ball(striker);

            if (overInfo[i] == "W")
            {
                ball->ballType = WICKET;
                ball->wicket = new Wicket();
                ball->runs.push_back(new Run(0));
                over->AddBall(ball);
                over->wickets++;
                over->fairDeliveries++;

                inningScore->wickets++;
                bowlerStat->wickets++;

                batsmanStat->balls++;
                batsmanStat->strikeRate = (batsmanStat->score / batsmanStat->balls) * 100;

                if (!battingOrder.empty())
                {
                    auto newStriker = battingOrder.front();
                    strikerEnd = newStriker;
                    battingOrder.pop_front();
                }
                else
                {
                    break;
                }
            }
            else if (overInfo[i] == "Wd")
            {
                ball->ballType = WIDEBALL;
                Run *run = new Run(1);
                run->runType = WIDE;
                ball->runs.push_back(run);

                over->AddBall(ball);
                over->runs++;

                inningScore->wides++;
                inningScore->extras++;
                inningScore->totalScore++;
            }
            else if (overInfo[i] == "Nb")
            {
                ball->ballType = NO_BALL;
                Run *run = new Run(1);
                run->runType = NOBALL;
                ball->runs.push_back(run);

                over->AddBall(ball);
                over->runs++;

                inningScore->noBalls++;
                inningScore->extras++;
                inningScore->totalScore++;
            }
            else
            {
                int runs = stoi(overInfo[i]);
                switch (runs)
                {
                case 4:
                {
                    Run *run = new Run(4);
                    run->runType = FOUR;
                    ball->runs.push_back(run);
                    inningScore->fours++;
                    batsmanStat->fours++;
                    break;
                }
                case 6:
                {
                    Run *run = new Run(6);
                    run->runType = SIX;
                    ball->runs.push_back(run);
                    inningScore->sixes++;
                    batsmanStat->sixes++;
                    break;
                }
                case 1:
                case 3:
                {
                    Run *run = new Run(runs);
                    run->runType = NORMAL;
                    ball->runs.push_back(run);
                    SwitchEnds(nonStrikerEnd, striker);
                    break;
                }
                case 0:
                case 2:
                {
                    Run *run = new Run(runs);
                    run->runType = NORMAL;
                    ball->runs.push_back(run);
                    break;
                }
                }
                over->AddBall(ball);
                over->runs += runs;
                over->fairDeliveries++;
                inningScore->totalScore += runs;

                batsmanStat->balls++;
                batsmanStat->score += runs;
                batsmanStat->strikeRate = (batsmanStat->score / batsmanStat->balls) * 100;
            }
        }
        int fairDeliveries = over->fairDeliveries;
        if (fairDeliveries == 6)
        {
            bowlerStat->overs += 1.0;
        }
        else
            bowlerStat->overs += fairDeliveries / 10.0;
        if (over->runs == 0)
        {
            bowlerStat->maidenOvers += 1;
        }
        else
        {
            bowlerStat->runsConceded += over->runs;
        }
        bowlerStat->economy = bowlerStat->runsConceded / bowlerStat->overs;

        overs.push_back(over);
        SwitchEnds(nonStrikerEnd, strikerEnd);
        DisplayScoreBoard();
    }

    void EndInning()
    {
        status = COMPLETED;
        endTime = time(0);
    }
};

#endif