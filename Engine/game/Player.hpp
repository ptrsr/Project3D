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
	Id _id;
	int _score = 0;

public:
	MovementBehaviour* _movement;

	bool _checked = false;

	Player(Id playerId, glm::vec2 boardPos);
	glm::vec2 getBoardPos();

	void addScore(int pScore);
	int  getScore();
	glm::vec2 getNextPos();
	Id getId();
};

#endif