# CricketScoreBoard


1. Run Driver.cpp to execute the app.
2. Input is provided in input.txt file.
3. Input format:

2  -> No. Of test cases
1  -> Test case number 1
No. of players for each team: 5
No. of overs: 2
Batting Order for team 1:
P1
P2
P3
P4
P5
Over 1:
Bowler: P7 -> Bowler who will bowl the over.
1
1
1
1
1
2
Over 2:
Bowler: P9
W
4
4
Wd
W
1
6
Batting Order for team 2:
P6
P7
P8
P9
P10
Over 1:
Bowler: P2
4
6
W
W
1
1
Over 2:
Bowler: P4
6
1
W
W


5. Test cases are separed by newline.
4. Output: 
    - ScoreBoard is displayed at end of every over.

```
Scoreboard after over 2
Batting score for Team2:
Batsman          Score   4s      6s      Balls   Strike Rate
P10              0       0       0       0       0.00
P6               10      1       1       3       300.00
P7               8       0       1       4       200.00
P8*              4       0       0       4       100.00
P9*              1       0       0       1       100.00

Total: 23/2
Extras: 0(WD 0, NB 0)
Overs: 2

Bowling stats for Team1:
Bowler           Overs   M       R       W       Economy
P1               1.0     0       14      1       14.00
P3               1.0     0       9       1       9.00
```
    
    - Match winner is displayed at end of each test case

```
Result of Match 3: Match tied
```
