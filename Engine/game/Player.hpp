#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "../game/Level.hpp"
#include "mge/behaviours/MovementBehaviour.hpp"
class Player : public GameObject
{
public:
	Player(PlayerId playerId);


};

#endif