#include "SpeedUp.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

#include "../game/Player.hpp"
#include "../game/Board.hpp"
#include "../game/Level.hpp"

SpeedUp::SpeedUp(float moveTime) : PickUp("speedup", moveTime)
{
	this->setMaterial(new LitMaterial(glm::vec3(0, 0, 1)));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "special_cube.obj"));
	this->scale(glm::vec3(0.5f));

	_minDelay = 4;
	_maxDelay = 10;

	reset();
}

void SpeedUp::applyPickUp(Player* pPlayer)
{
	pPlayer->_movement->fireAbility(2);
}