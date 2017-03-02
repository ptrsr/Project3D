#include "../game/Player.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitMaterial.hpp"

#include "Enums.hpp"

Player::Player(Id playerId, glm::vec2 boardPos, float pTime, float pWait) : GameObject("temp")
{
	_name = "Player" + playerId;
	_id = playerId;

	this->setLocalPosition(glm::vec3(boardPos.x, 1.0f, boardPos.y)); 

	_movement = new MovementBehaviour(this, boardPos, 1.0f, pTime, pWait);
	this->setBehaviour(_movement);

	//this->scale(glm::vec3(0.3f, 0.3f, 0.8f));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "elementcube.obj"));

	glm::vec3 color = glm::vec3(1, 0, 0);

	if (playerId == water)
		color = glm::vec3(0, 0, 1);

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