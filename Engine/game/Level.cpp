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
	spawnPickUp(new ScoreCube());

	Board* _board = new Board();
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
	_board->setOwner(pPlayer->getBoardPos(), pPlayer->getId());
}

void Level::update(float pStep)
{
	_curTime += pStep;

	std::cout << "test" << std::endl;

	if (_curTime >= _totalMoveTime)
	{
		for each (PickUp* pickUp in PickUp::getPickUps())
			pickUp->step();

		_curTime -= _totalMoveTime;
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

	Player* player = new Player(p1, pBoardPos); 
	player->setParent(this);
	_players.push_back(player);
}

void Level::spawnPickUp(PickUp* pPickUp)
{
	_pickups.push_back(pPickUp);
	pPickUp->setParent(Level::get());
}

Level::~Level()
{
	for each (Player* player in _players)
		delete player;

	for each (PickUp* pickUp in _pickups)
		delete pickUp;

	delete _board;
}