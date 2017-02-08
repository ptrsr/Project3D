#include "../game/Player.hpp"

Player::Player(PlayerId playerId, std::string name, int xTile, int yTile, Level * level) :GameObject(name)
{
	//Getting the position of the player
	GameObject * gObj = level->getObject(0, 0);
	glm::vec3 position = gObj->getLocalPosition();


	//Creating the player
	GameObject * player = new GameObject(name, glm::vec3(0,1,0));
	player->translate(glm::vec3(0, 0.3f, 0));
	ColorMaterial * colorMaterial = new ColorMaterial(glm::vec3(0.7f,0,0));
	Mesh* mesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	player->setMaterial(colorMaterial);


	//Setting the color of the cube below the player
	gObj->setMaterial(new ColorMaterial(player->getMaterial()->getColor()));
	player->setBehaviour(new MovementBehaviour());

	player->scale(glm::vec3(0.3f, 0.3f, 0.3f));
	player->setMesh(mesh);
	World::add(player);
}
