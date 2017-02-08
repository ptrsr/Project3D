#include "../game/Level.hpp"
#include "../game/Player.hpp"

Level::Level() :GameObject("level")
{
	_cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	initializeLevel();
	std::string name = "Player1";

	_player = new Player(PlayerId::Player1);
	
}

void Level::initializeLevel() 
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");

	for (int i = 0; i <= _xTileCount; i++) {
		for (int j = 0; j <= _zTileCount; j++) {

			std::string cubeName = "Cube: Row: " + to_string(i);
			cubeName += " Column: " + to_string(j);

			glm::vec3 color;

			if ((j + i) % 2)
				color = glm::vec3(1);
			else
				color = glm::vec3(0.4f);

			GameObject * plane = new GameObject(cubeName, glm::vec3(i, 0, j));
			plane->setMesh(planeMesh);

			plane->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, color));

			_boardArray[i][j] = plane;
			World::add(plane);


			glm::vec3 pos = plane->getLocalPosition();
		}
	}
}

GameObject* Level::getObject(int xTile,int zTile) {
	GameObject* gObj = _boardArray[xTile][zTile];
	return gObj;
}