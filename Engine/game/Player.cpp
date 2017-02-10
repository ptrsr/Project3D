#include "../game/Player.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/LitMaterial.hpp"

Player::Player(Tile::Id playerId, Tile* boardArray[9][9]) : GameObject("temp")
{
	_name = "Player" + playerId;


	//Setting the color of the cube below the player
	this->setBehaviour(new MovementBehaviour(this, boardArray, 1.0f, 0.8f, 0.3f));

	//this->scale(glm::vec3(0.3f, 0.3f, 0.8f));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "elementcube.obj"));
	this->setLocalPosition(glm::vec3(0, 0.5f, 0));
	this->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3(1, 0, 0)));
	World::add(this);

};
