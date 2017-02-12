#ifndef TILE_H
#define TILE_H

#include "mge/core/GameObject.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "Enums.hpp"

class Tile : public GameObject
{
public:
	Tile(glm::vec3 pPosition, Mesh* pMesh);

	void SetOwner(Id pPlayer);

	LitMaterial* _material;

private:
	Id _owner = none;

};

#endif