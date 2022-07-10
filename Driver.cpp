#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Services/MatchService.cpp"

using namespace std;

int main()
{
    string line;
    int tests;
    ifstream input("input.txt");
    MatchService *matchService = MatchService::GetInstance();
    if (input.is_open())
    {
        getline(input, line);
        tests = stoi(line);
        int numberOfPlayers;
        int overs;
        int inningId;
        vector<string> battingOrder;
        for (int i = 0; i < tests; i++)
        {
            getline(input, line);
            getline(input, line);

            numberOfPlayers = line[line.length() - 1] - '0';
            getline(input, line);
            overs = line[line.length() - 1] - '0';
            getline(input, line);
            int matchId = matchService->ScheduleMatch(numberOfPlayers, overs);
            // Batting order of team 1
            for (int j = 0; j < numberOfPlayers; j++)
            {
                getline(input, line);
                battingOrder.push_back(line);
            }

            vector<string> overInfo;
            string bowler;

            matchService->StartMatch(matchId);

            inningId = 1;
            matchService->StartInning(matchId, inningId, overs, battingOrder, "Team1", "Team2");
            battingOrder.clear();
            // overs info inning 1
            getline(input, line);
            for (int k = 1; k <= overs;)
            {
                getline(input, line);
                if (line.rfind("Over", 0) == 0 || line.rfind("Batting", 0) == 0 || line == "")
                {
                    matchService->RecordOver(matchId, inningId, overInfo, bowler, k);
                    overInfo.clear();
                    k++;
                }
                else if (line.rfind("Bowler: ", 0) == 0)
                {
                    bowler = line.substr(8, line.length() - 8);
                }
                else
                {
                    overInfo.push_back(line);
                }
            }
            matchService->EndInning(matchId, inningId);

            // Batting order of team 2
            for (int j = 0; j < numberOfPlayers; j++)
            {
                getline(input, line);
                battingOrder.push_back(line);
            }
            inningId = 2;
            matchService->StartInning(matchId, inningId, overs, battingOrder, "Team2", "Team1");
            battingOrder.clear();
            // overs info inning 2
            getline(input, line);
            for (int k = 1; k <= overs;)
            {
                getline(input, line);
                if (line.rfind("Over", 0) == 0 || line.rfind("Batting", 0) == 0 || line == "")
                {
                    matchService->RecordOver(matchId, inningId, overInfo, bowler, k);
                    overInfo.clear();
                    k++;
                }
                else if (line.rfind("Bowler: ", 0) == 0)
                {
                    bowler = line.substr(8, line.length() - 8);
                }
                else
                {
                    overInfo.push_back(line);
                }
            }
            matchService->EndInning(matchId, inningId);
            matchService->CheckWinner(matchId, inningId);
        }
        input.close();
    }

    return 0;
}