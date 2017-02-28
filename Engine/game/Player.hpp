#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "mge/behaviours/PlayerBehaviour.hpp"
#include "mge/behaviours/WindBehaviour.hpp"
#include "mge/behaviours/WaterBehaviour.hpp"
#include "mge/behaviours/FireBehaviour.hpp"
#include "mge/behaviours/EarthBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "Tile.hpp"

#include "Enums.hpp"

class Player : public GameObject
{
private:
	Id _id;
	int _score;

public:
	PlayerBehaviour* _movement;

	bool _checked = false;

	Player(Id playerId, glm::vec2 boardPos);
	glm::vec2 getBoardPos();

	void addScore(int pScore);
	glm::vec2 getNextPos();
	Id getId();
};

#endif