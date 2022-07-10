#ifndef _Player_
#define _Player_

#include <string>

using namespace std;

class Player
{
public:
    string name;
    Player(string name) : name(name)
    {
    }
};

#endif