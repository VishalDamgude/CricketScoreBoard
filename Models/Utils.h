#ifndef _Utils_
#define _Utils_

enum MatchStatus
{
    IN_PROGRESS,
    FINISHED,
    DRAWN,
    CANCELLED
};

enum InningStatus
{
    STARTED,
    COMPLETED
};

enum WicketType
{
    BOWLED,
    CAUGHT,
    STUMPED,
    RUNOUT,
    LBW,
    RETIRED_HURT,
};

enum BallType
{
    FAIR_DELIVERY,
    WIDEBALL,
    WICKET,
    NO_BALL,
};

enum RunType
{
    NORMAL,
    FOUR,
    SIX,
    LEGBYE,
    WIDE,
    NOBALL,
    OVERTHROW,
};

#endif