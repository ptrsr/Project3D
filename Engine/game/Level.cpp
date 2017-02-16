#include "../game/Level.hpp"
#include "../game/Player.hpp"
#include "Tile.hpp"

Level::Level(glm::vec2 pSize) :GameObject("level")
{
	_size = pSize;
	//_boardArray = new 

	_cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	initializeLevel();

	_player = new Player(Tile::p1, _boardArray);
	
}
void Level::initializeLevel() 
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	for (int i = 0; i < _size.x; i++) {
		for (int j = 0; j < _size.y; j++) {

			glm::vec3 color;

			if ((j + i) % 2)
				color = glm::vec3(1);
			else
				color = glm::vec3(0.4f);

			Tile * tile = new Tile(glm::vec3(i, 0, j), planeMesh);
			tile->_material->setColor(color);

			_boardArray[j][i] = tile;
		}
	}
}

GameObject* Level::getObject(int xTile,int zTile) {
	GameObject* gObj = _boardArray[xTile][zTile];
	return gObj;
}

Level::~Level()
{
	for (int i = 0; i <= _size.x; i++) {
		for (int j = 0; j <= _size.y; j++) {

			Tile* tile = _boardArray[j][i];

			World::remove(tile);
			delete tile;
		}
	}

	World::remove(_player);
	delete _player;
}