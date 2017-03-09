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

	glm::vec2 getBoardPos();

	vector<Tile*> getConnections();

	LitMaterial* _material;

	//loop fill
	bool _connected = true;

	//pathfinding
	float _costCurrent;
	float _costEstimate;

	Tile* _parentTile = NULL;

private:
	glm::vec2 _boardPos;
	Id _owner = Id::empty;

};

#endif