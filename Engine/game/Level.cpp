#include "../game/Level.hpp"
#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

#include "Enums.hpp"
#include "PickUps/ScoreCube.hpp"

Level* Level::_level;

Level::Level() :GameObject("level")
{
	spawnPlayer(Id::p1, glm::vec2(0, 0));
	spawnPlayer(Id::p3, glm::vec2(8, 8));
	spawnPickUp(new ScoreCube());

	_board = new Board();
	_board->setParent(this);
	World::add(this);
}

Level* Level::get()
{
	if (!_level)
		_level = new Level();

	return _level;
}

std::vector<Player*> Level::getPlayers()
{
	return Level::get()->_players;
}

std::vector<PickUp*> Level::getPickUps()
{
	return Level::get()->_pickups;
}

Board* Level::getBoard()
{
	return Level::get()->_board;
}

void Level::step(Player* pPlayer)
{
	Level* level = Level::get();

	level->_board->setOwner(pPlayer->getBoardPos(), pPlayer->getId());

	for each (PickUp* pickUp in level->_pickups)
		if (pPlayer->getBoardPos() == pickUp->getBoardPos())
			pickUp->applyPickUp(pPlayer);
}

bool Level::checkAvailable(Player* pPlayer)
{
	Level* level = Level::get();
	glm::vec2 nextPos = pPlayer->getNextPos();

	if (level->_board->outOfBounds(nextPos))
		return false;

	for each (Player* player in level->_players)
	{
		if (pPlayer == player)
			continue;

		if (player->getNextPos() == nextPos)
			return false;
	}
	return true;
}

void Level::update(float pStep)
{
	_curTime += pStep;

	if (_curTime > _totalMoveTime)
	{
		_curTime -= _totalMoveTime;

		for each (PickUp* pickUp in _pickups)
			pickUp->step();
	}
}

void Level::spawnPlayer(Id pPlayerId, glm::vec2 pBoardPos)
{
	for each (Player* player in _players)
	{
		if (player->getId() == pPlayerId)
		{
			std::cout << "Error: Player already exists" << std::endl;
			return;
		}
	}
	Player* player = new Player(pPlayerId, pBoardPos);
	World::add(player);
	_players.push_back(player);
}

void Level::spawnPickUp(PickUp* pPickUp)
{
	_pickups.push_back(pPickUp);
	pPickUp->setParent(this);
}

Level::~Level() { }