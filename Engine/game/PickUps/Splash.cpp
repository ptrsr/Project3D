#include "../game/PickUps/Splash.hpp"

#include "mge/materials/TextureMaterial.hpp"
#include "mge/auxiliary/AudioManager.h"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

#include "../game/Player.hpp"
#include "../game/Board.hpp"
#include "../game/Level.hpp"

Splash::Splash(float moveTime) : PickUp("Splash", moveTime)
{
	_type = Effect::splash;
	this->setMaterial(new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "splashcube.png")));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "special_cube.obj"));
	this->scale(glm::vec3(0.5f));

	_minDelay = 4;
	_maxDelay = 10;

	reset();
}

void Splash::applyPickUp(Player* pPlayer)
{
	Level::get()->CreatePacket(pPlayer->getId(), Effect::splash, pPlayer->getBoardPos());
}