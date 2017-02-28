#ifndef TILE_H
#define TILE_H

#include "mge/core/GameObject.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "Enums.hpp"

class Tile : public GameObject
{


public:
	Tile(glm::vec3 pPosition, Mesh* pMesh);

	void setOwner(Id pPlayer);
	Id getOwner();

	LitMaterial* _material;

private:
	Id _owner = Id::empty;

};

#endif