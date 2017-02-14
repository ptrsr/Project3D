#include "../game/Player.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitMaterial.hpp"

#include "Enums.hpp"

Player::Player(Id playerId, glm::vec2 boardPos) : GameObject("temp")
{
	_name = "Player" + playerId;

	this->setLocalPosition(glm::vec3(boardPos.x, 0.5f, boardPos.y)); 
	this->setBehaviour(new MovementBehaviour(this, playerId, boardPos, 1.0f, 0.8f, 0.3f));

	//this->scale(glm::vec3(0.3f, 0.3f, 0.8f));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "elementcube.obj"));
	this->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3(1, 0, 0)));
	World::add(this);

};
