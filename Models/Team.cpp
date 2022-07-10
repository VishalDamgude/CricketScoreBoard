#ifndef _Team_
#define _Team_

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Player.cpp"
using namespace std;

class Team
{
public:
    string name;
    int noOfPlayers;
    map<string, shared_ptr<Player>> players;

public:
    Team(string name, int n, int offset) : name(name), noOfPlayers(n)
    {
        int totalPlayers = offset + noOfPlayers - 1;
        for (int i = offset; i <= totalPlayers; i++)
        {
            string name = "P" + to_string(i);
            auto p = make_shared<Player>(name);
            players[name] = p;
        }
    }

    shared_ptr<Player> GetPlayer(string name)
    {
        auto it = players.find(name);
        if (it != players.end())
            return it->second;
        return nullptr;
    }

    ~Team() {}
};

#endif