#include "ScoreCube.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
ScoreCube::ScoreCube(std::vector<Player*> pPlayers) : PickUp("ScoreCube", pPlayers)
{
	this->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3(0, 1, 0)));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj"));
	this->scale(glm::vec3(0.3f));
}