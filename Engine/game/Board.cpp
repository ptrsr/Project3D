#include "../game/Board.hpp"
#include "Tile.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

Board* Board::_board;

Board::Board()
{
	initializeBoard();
}

Board* Board::get()
{
	if (!_board)
		_board = new Board();

	return _board;
}

void Board::setOwner(glm::vec2 boardPos, Id player)
{
	Board* board = get();

	if (boardPos.x < 0 || boardPos.y < 0 || boardPos.x > board->_size.x || boardPos.y > board->_size.y)
		return;

	Tile* tile = board->_boardArray[(int)boardPos.x][(int)boardPos.y];

	if (tile)
		tile->SetOwner(player);
}

void Board::initializeBoard() 
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

Board::~Board()
{
	for (int i = 0; i < _size.x; i++)
		for (int j = 0; j < _size.y; j++)
				delete _boardArray[i][j];
}