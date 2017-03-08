#include "../game/Board.hpp"
#include "Tile.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/auxiliary/MeshCache.hpp"

#include "Player.hpp"
#include "Level.hpp"

#include "mge/auxiliary/PathFinder.hpp"
#include "mge/auxiliary/BreathFirst.hpp"


Board::Board() : GameObject("Board")
{
	initializeBoard();
}

void Board::setOwner(glm::vec2 pBoardPos, Id player)
{
	if (outOfBounds(pBoardPos))
		return;

	_boardArray[(int)pBoardPos.x][(int)pBoardPos.y]->setOwner(player);
}

Id Board::getOwnerOfTile(glm::vec2 pBoardPos) {
	if (outOfBounds(pBoardPos))
		return Id::none;

	return _boardArray[(int)pBoardPos.x][(int)pBoardPos.y]->getOwner();
}

void Board::checkTile(Tile* pTile)
{
	_tilesToBeChecked.push_back(pTile);
}

void Board::resolveAreas()
{
	BreathFirst breathFirst;

	while (_tilesToBeChecked.size() != 0)
	{
		Tile* tile = _tilesToBeChecked[0];
		std::cout << !PathFinder::canReach(tile, Level::getBoard()->getTile(Level::getPlayer(tile->getOwner())->getBoardPos())) << std::endl;


		if (tile->_connected == true && !PathFinder::canReach(tile, Level::getBoard()->getTile(Level::getPlayer(tile->getOwner())->getBoardPos())))
			breathFirst.disconnect(tile);

		_tilesToBeChecked.erase(_tilesToBeChecked.begin());
	}
}

Tile* Board::getTile(glm::vec2 pBoardPos)
{
	if (outOfBounds(pBoardPos))
		return nullptr;

	return _boardArray[(int)pBoardPos.x][(int)pBoardPos.y];
}

void Board::initializeBoard() 
{
	Mesh* planeMesh;
	if (MeshCache::exists(config::MGE_MODEL_PATH + "playfield_tile.obj")) {
		planeMesh = MeshCache::find(config::MGE_MODEL_PATH + "playfield_tile.obj");
	}
	else {
		planeMesh = Mesh::load(config::MGE_MODEL_PATH + "playfield_tile.obj");
		MeshCache::push(planeMesh);
	}

	for (int i = 0; i < _size.x; i++) {
		for (int j = 0; j < _size.y; j++) 
		{
			Tile * tile = new Tile(glm::vec3(j, 0.f, i), planeMesh);
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
				tile->setOwner(none);
			}
		}
	}
	return score;
}

void Board::fireAbility(glm::vec2 pBoardPos)
{
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			glm::vec2 pos = pBoardPos + glm::vec2(i, j);

			if (!outOfBounds(pos))
			{
				Tile* tile = _boardArray[(int)pos.x][(int)pos.y];

				if (tile->getOwner() != none)
					tile->setOwner(p1);
			}
		}
	}
}

void Board::earthAbility(glm::vec2 pBoardPos)
{
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			glm::vec2 pos = pBoardPos + glm::vec2(i, j);

			if (!outOfBounds(pos))
			{
				Tile* tile = _boardArray[(int)pos.x][(int)pos.y];

				if (tile->getOwner() == none)
					tile->setOwner(p3);
			}
		}
	}
}