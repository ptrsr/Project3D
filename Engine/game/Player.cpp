#include "../game/Player.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitMaterial.hpp"

#include "Enums.hpp"

Player::Player(Id playerId, glm::vec2 boardPos, float pTime, float pWait, bool controlled) : GameObject("temp")
{
	_name = "Player" + playerId;
	_id = playerId;

	this->setLocalPosition(glm::vec3(boardPos.x, 1.0f, boardPos.y)); 

	_movement = new MovementBehaviour(this, boardPos, 1.0f, pTime, pWait, controlled);
	this->setBehaviour(_movement);

	//this->scale(glm::vec3(0.3f, 0.3f, 0.8f));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "elementcube.obj"));

	glm::vec3 color(
		playerId == Id::p1 ? 1 : playerId == Id::p2 ? 0 : playerId == Id::p3 ? 0 : 0.87f,
		playerId == Id::p2 ? 1 : playerId == Id::p4 ? 0.72f : 0,
		playerId == p3 ? 1 : playerId == Id::p4 ? 0.53f : 0);

	this->setMaterial(new LitMaterial(color));
};

void Player::addScore(int pScore)
{
	_score += pScore;
	std::cout << "Player " << _id << " scored: " << pScore << std::endl;
}

int Player::getScore()
{
	return _score;
}

glm::vec2 Player::getBoardPos()
{
	return _movement->getBoardPos();
}

void Player::setBoardPos(glm::vec2 pos)
{
	this->setLocalPosition(glm::vec3(pos.x, 1.0f, pos.y));
	_movement->setBoardPos(pos);
}

glm::vec2 Player::getNextPos()
{
	return _movement->getNextPos();
}

Id Player::getId()
{
	return _id;
}

void Player::enableAbility()
{
	_movement->enableAbility();
}

bool Player::IsControlled()
{
	return _movement->IsControlled();
}