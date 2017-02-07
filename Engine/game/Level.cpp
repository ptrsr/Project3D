#include "../game/Level.hpp"

Level::Level(int xTiles, int yTiles, World * world) :GameObject("level")
{
	_world = world;
	_xTileCount = xTiles;
	_yTileCount = yTiles;

	_cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	initializeLevel();
}

void Level::initializeLevel() {

	_boardArray = new int*[_xTileCount]; // dynamic array (size 10) of pointers to int

	for (int i = 0; i < _xTileCount; ++i) {
		_boardArray[i] = new int[_yTileCount];
		// each i-th pointer is now pointing to dynamic array (size 10) of actual int values
	}

	for (int i = 0; i <= _xTileCount; i++) {
		for (int j = 0; j <= _yTileCount; j++) {
			std::string cubeName = "Cube: Row: " + to_string(i);
			cubeName += " Column: " + to_string(j);
			GameObject * cube = new GameObject(cubeName, glm::vec3(i, 0, j));
			cube->scale(glm::vec3(0.4f, 1,0.4f));
			LitMaterial * colorMaterial = new LitMaterial(LitMaterial::Lit::fragment);
			cube->setMesh(_cubeMesh);
			cube->setMaterial(colorMaterial);
			_world->add(cube);
			glm::vec3 pos = cube->getLocalPosition();
			std::string posString = " X:" + to_string(pos.x);
			posString += " Y:" + to_string(pos.y);
			posString += " Z:" + to_string(pos.z);

			cout << cubeName << posString <<endl;
		}
	}
	
}