#include "../game/Player.hpp"

Player::Player(PlayerId playerId, std::string name, int xTile, int yTile, Level * level) :GameObject(name)
{
	glm::vec3 position = level->getPositionOfTile(0, 0);

	GameObject * player = new GameObject(name, glm::vec3(0,1,0));
	player->translate(glm::vec3(0, 0.3f, 0));

	LitMaterial * litMaterial = new LitMaterial(LitMaterial::Lit::fragment);

	Mesh* mesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	player->setMaterial(litMaterial);

	player->scale(glm::vec3(0.3f, 0.3f, 0.3f));
	player->setMesh(mesh);
	World::add(player);
}
