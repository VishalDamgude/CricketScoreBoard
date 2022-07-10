#include <iostream>
#include <map>
#include <memory>
#include "../Models/Match.cpp"
using namespace std;

class MatchRepository
{
    map<int, Match *> matches;

public:
    MatchRepository() {}

    void CreateMatch(int matchId, int noOfPlayers, int overs)
    {
        Match *match = new Match(matchId);

        shared_ptr<Team> team1 = make_shared<Team>("Team1", noOfPlayers, 1);
        shared_ptr<Team> team2 = make_shared<Team>("Team2", noOfPlayers, noOfPlayers + 1);

        match->AddTeam(team1);
        match->AddTeam(team2);

        matches.insert({matchId, match});
    }

    Match *GetMatch(int matchId)
    {
        auto it = matches.find(matchId);
        if (it != matches.end())
        {
            return it->second;
        }
        return nullptr;
    }
};