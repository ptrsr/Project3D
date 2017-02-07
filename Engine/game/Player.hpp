#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../game/Level.hpp"

class Player : public GameObject
{
public:
	Player(PlayerId playerId, std::string name,int xTile, int yTile, Level level);


};

#endif