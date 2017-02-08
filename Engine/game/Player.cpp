#include "../game/Player.hpp"

Player::Player(PlayerId playerId) : GameObject("temp")
{
	_name = "Player" + playerId;


	//Setting the color of the cube below the player
	this->setBehaviour(new MovementBehaviour(this));

	this->scale(glm::vec3(0.3f, 0.3f, 0.3f));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj"));
	this->setLocalPosition(glm::vec3(5, 0.3f, 5));
	this->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3(1, 0, 0)));
	World::add(this);

}
