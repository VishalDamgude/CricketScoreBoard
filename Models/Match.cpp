#ifndef _Match_
#define _Match_

#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include "Inning.cpp"

using namespace std;

class Match
{
public:
    int id = 0;
    time_t startTime;
    time_t endTime;
    MatchStatus result;

    map<string, shared_ptr<Team>> teams;
    map<int, Inning *> innings;
    int targetScore = 0;
    Team *winner;
    Match(int id) : id(id)
    {
    }

    void startMatch()
    {
        startTime = time(0);
    }

    void AddTeam(shared_ptr<Team> team)
    {
        teams.insert({team->name, team});
    }

    void DisplayTeam(string name)
    {
        cout << "Displaying team " << name << endl;
        auto team = GetTeam(name);
        if (team)
        {
            for (auto it : team->players)
            {
                cout << it.first << " " << it.second->name << endl;
            }
        }
    }
    shared_ptr<Team> GetTeam(string name)
    {
        auto it = teams.find(name);
        if (it != teams.end())
            return it->second;
        return nullptr;
    }
    void AddInning(int inningId, Inning *inning)
    {
        innings.insert({inningId, inning});
    }

    Inning *GetInning(int inningId)
    {
        auto it = innings.find(inningId);
        if (it != innings.end())
            return it->second;
        return nullptr;
    }

    void StartInning(int inningId, int overs, vector<string> &battingOrder, string battingTeam, string bowlingTeam)
    {
        Inning *inning = new Inning(overs, inningId);
        inning->battingTeam = GetTeam(battingTeam);
        inning->bowlingTeam = GetTeam(bowlingTeam);
        inning->InitializeBattingOrder(battingOrder);
        inning->InitializeBatsmanStats(id);
        cout << "Starting Inning " << inningId << ":" << endl;
        if (targetScore != 0)
        {
            cout << "Target for " << inning->battingTeam->name << ": " << targetScore << endl;
        }
        inning->StartInning();
        AddInning(inningId, inning);
    }

    void EndInning(int inningId)
    {
        Inning *inning = GetInning(inningId);
        inning->EndInning();
        if (inningId == 1)
            targetScore = inning->inningScore->totalScore + 1;
    }

    void CheckWinner(int inningId)
    {
        Inning *inning = GetInning(inningId);
        endTime = time(0);
        result = FINISHED;

        printf("\nResult of Match %d: ", id);
        if (inning->inningScore->totalScore >= targetScore)
        {
            cout << inning->battingTeam->name << " won the match by " << inning->battingTeam->players.size() - inning->inningScore->wickets << " wickets" << endl;
        }
        else if (targetScore - inning->inningScore->totalScore == 1)
        {
            cout << "Match tied" << endl;
        }
        else
        {
            cout << inning->bowlingTeam->name << " won the match by " << targetScore - inning->inningScore->totalScore - 1 << " runs" << endl;
        }
        cout << endl;
    }
};

#endif