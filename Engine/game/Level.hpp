#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/config.hpp"
using namespace std;

enum PlayerId {
	Player1 = 1,
	Player2 = 2,
	Player3 = 3,
	Player4 = 4
};


class Level : public GameObject
{
	
public:
	Level(int xTiles, int yTiles, World * world);
	

private:
	World * _world;
	int **_boardArray;
	int _xTileCount;
	int _yTileCount;
	Mesh * _cubeMesh;
	void initializeLevel();

};
#endif