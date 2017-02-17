#include "../game/Board.hpp"
#include "Tile.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

Board::Board() : GameObject("Board")
{
	initializeBoard();
}

void Board::setOwner(glm::vec2 boardPos, Id player)
{
	if (outOfBounds(boardPos))
		return;

	_boardArray[(int)boardPos.x][(int)boardPos.y]->setOwner(player);
}

void Board::initializeBoard() 
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "playfield_tile.obj");

	for (int i = 0; i < _size.x; i++) {
		for (int j = 0; j < _size.y; j++) 
		{
			Tile * tile = new Tile(glm::vec3(j, 0, i), planeMesh);

			_boardArray[j][i] = tile;
			tile->setParent(this);
		}
	}
}

bool Board::outOfBounds(glm::vec2 pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= 9 || pos.y >= 9)
		return true;

	return false;
}

int Board::getScore(Id pPlayerId)
{
	int score = 0;

	for (int i = 0; i < _size.x; i++) {
		for (int j = 0; j < _size.y; j++) {

			Tile* tile = _boardArray[j][i];

			if (tile->getOwner() == pPlayerId)
			{
				score++;
				tile->setOwner(Id::empty);
			}
		}
	}
	return score;
}