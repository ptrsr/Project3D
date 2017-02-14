#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "Tile.hpp"

#include "Enums.hpp"

class Player : public GameObject
{
private:
	MovementBehaviour* _movement;

public:
	Player(Id playerId, glm::vec2 boardPos);
	glm::vec2 getBoardPos();

};

#endif