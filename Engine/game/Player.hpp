#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "Tile.hpp"

class Player : public GameObject
{
public:
	Player(Tile::Id playerId, Tile* boardArray[9][9]);


};

#endif