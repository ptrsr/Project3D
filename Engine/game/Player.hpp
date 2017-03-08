#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include "Tile.hpp"

#include "Enums.hpp"

class PickUp;

class Player : public GameObject
{
private:
	Id _id;
	int _score = 0;
	PickUp* _pickUp = NULL;

public:
	MovementBehaviour* _movement;

	bool _checked = false;

	Player(Id playerId, glm::vec2 boardPos, float pMoveTime, float pWait, bool controlled);
	glm::vec2 getBoardPos();
	void setBoardPos(glm::vec2 pos);
	glm::vec2 getNextPos();

	void StorePickUp(PickUp* pickUp);
	void UsePickUp();
	void addScore(int pScore);
	int getScore();
	Id getId();
	bool IsControlled();
};

#endif