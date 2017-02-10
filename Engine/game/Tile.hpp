#ifndef TILE_H
#define TILE_H

#include "mge/core/GameObject.hpp"
#include "mge/materials/LitMaterial.hpp"

class Tile : public GameObject
{
public:
	enum Id {
		none,
		p1,
		p2,
		p3,
		p4
	};

	Tile(glm::vec3 pPosition, Mesh* pMesh);

	void SetOwner(Id pPlayer);

	LitMaterial* _material;

private:
	Id _owner = none;

};

#endif