#include <iostream>
#include <map>
#include <memory>
#include "../Repository/MatchRepository.cpp"
using namespace std;

class MatchService
{
    static int matchCounter;
    MatchRepository *matchRepo;
    static MatchService *matchService;

    MatchService()
    {
        matchRepo = new MatchRepository();
    }

public:
    static MatchService *GetInstance()
    {
        if (matchService == nullptr)
        {
            matchService = new MatchService();
        }
        return matchService;
    }

    int ScheduleMatch(int noOfPlayers, int overs)
    {
        matchCounter++;
        matchRepo->CreateMatch(matchCounter, noOfPlayers, overs);
        return matchCounter;
    }

    int StartMatch(int matchId)
    {

        Match *match = matchRepo->GetMatch(matchId);
        if (match)
        {
            cout << "Starting Match " << matchId << ":" << endl;
            match->startMatch();
        }

        return 0;
    }

    int StartInning(int matchId, int inningId, int overs, vector<string> &battingOrder, string battingTeam, string bowlingTeam)
    {

        Match *match = matchRepo->GetMatch(matchId);
        if (match)
        {
            match->StartInning(inningId, overs, battingOrder, battingTeam, bowlingTeam);
        }

        return 0;
    }

    int RecordOver(int matchId, int inningId, vector<string> &overInfo, string bowlerName, int overNumber)
    {

        Match *match = matchRepo->GetMatch(matchId);
        if (match)
        {
            Inning *inning = match->GetInning(inningId);
            if (inning)
            {
                shared_ptr<Player> bowler = inning->bowlingTeam->GetPlayer(bowlerName);
                if (bowler)
                {
                    inning->RecordOver(matchId, overInfo, bowler, overNumber);
                }
            }
        }

        return 0;
    }

    int EndInning(int matchId, int inningId)
    {

        Match *match = matchRepo->GetMatch(matchId);
        if (match)
        {
            match->EndInning(inningId);
        }

        return 0;
    }
    int CheckWinner(int matchId, int inningId)
    {

        Match *match = matchRepo->GetMatch(matchId);
        if (match)
        {
            match->CheckWinner(inningId);
        }

        return 0;
    }
};

int MatchService::matchCounter = 0;
MatchService *MatchService::matchService = nullptr;
