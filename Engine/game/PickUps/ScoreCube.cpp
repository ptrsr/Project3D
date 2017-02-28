#include "ScoreCube.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

#include "../game/Player.hpp"
#include "../game/Board.hpp"
#include "../game/Level.hpp"

ScoreCube::ScoreCube() : PickUp("ScoreCube")
{
	this->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3(0, 1, 0)));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj"));
	this->scale(glm::vec3(0.3f));

	_minDelay = 4;
	_maxDelay = 10;

	reset();
}

glm::vec2 ScoreCube::applyPickUp(Player* pPlayer)
{
	glm::vec2 oldPos = getBoardPos();
	int score = Level::getBoard()->getScore(pPlayer->getId());
	pPlayer->addScore(score);
	Level::get()->CreatePacket(pPlayer->getId(), score);
	reset();

	return oldPos;
}