#include "../game/PickUps/Speed.hpp"

#include "mge/materials/LitMaterial.hpp"
#include "mge/auxiliary/AudioManager.h"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

#include "../game/Player.hpp"
#include "../game/Board.hpp"
#include "../game/Level.hpp"

Speed::Speed(float moveTime) : PickUp("Speed", moveTime)
{
	_type = Effect::speed;
	this->setMaterial(new LitMaterial(glm::vec3(0, 1, 1)));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "special_cube.obj"));
	this->scale(glm::vec3(0.5f));

	_minDelay = 4;
	_maxDelay = 10;

	reset();
}

void Speed::applyPickUp(Player* pPlayer)
{
	Level::get()->CreatePacket(pPlayer->getId(), Effect::speed, pPlayer->getBoardPos());
}