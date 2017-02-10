#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/config.hpp"

#include "../game/Tile.hpp"

class Level : public GameObject
{
	
public:
	Level(glm::vec2 pSize);
	GameObject* getObject(int xTile, int zTile);
private:
	glm::vec2 _size;
	GameObject * _player;

	Tile* _boardArray[9][9];
	void initializeLevel();
	Mesh * _cubeMesh;

	~Level();
};
#endif