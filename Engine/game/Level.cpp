#include "../game/Level.hpp"
#include "../game/Player.hpp"

Level::Level() {}

Level::Level(World * world) :GameObject("level")
{
	_world = world;

	_cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	initializeLevel();
	std::string name = "Player1";
	Player * player = new Player(PlayerId::Player1, name, 0, 0,this);
}

void Level::initializeLevel() {

	for (int i = 0; i <= _xTileCount; i++) {
		for (int j = 0; j <= _zTileCount; j++) {

			std::string cubeName = "Cube: Row: " + to_string(i);
			cubeName += " Column: " + to_string(j);

			GameObject * cube = new GameObject(cubeName, glm::vec3(i, 0, j));
			cube->scale(glm::vec3(0.4f, 1,0.4f));
			LitMaterial * litMaterial = new LitMaterial(LitMaterial::Lit::fragment);
			cube->setMesh(_cubeMesh);
			cube->setMaterial(litMaterial);
			_boardArray[i][j] = cube;
			_world->add(cube);


			glm::vec3 pos = cube->getLocalPosition();
			std::string posString = " X:" + to_string(pos.x);
			posString += " Y:" + to_string(pos.y);
			posString += " Z:" + to_string(pos.z);

			cout << cubeName << posString <<endl;
		}
	}
}

GameObject* Level::getObject(int xTile,int zTile) {
	GameObject* gObj = _boardArray[xTile][zTile];
	return gObj;
}