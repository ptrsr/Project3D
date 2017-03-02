#include "../game/Level.hpp"
#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

#include "Enums.hpp"
#include "PickUps/ScoreCube.hpp"

Level* Level::_level;

Level::Level() :GameObject("level")
{
	setLocalPosition(glm::vec3(-8.5f, 0, 0.5f));

	spawnPlayer(Id::p1, glm::vec2(0, 0));
	spawnPlayer(Id::p3, glm::vec2(8, 8));
	spawnPickUp(new ScoreCube(_totalTime));

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

void Level::reset()
{
	delete _level;
	_level = new Level();
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

void Level::ApplyPickUp(Player* pPlayer)
{
	for each (PickUp* pickUp in Level::getPickUps())
		if (pickUp->getBoardPos() == pPlayer->getBoardPos())
			pickUp->applyPickUp(pPlayer);
}

void Level::update(float pStep)
{
	_curTime += pStep;

	for each (PickUp* pickUp in _pickups)
		pickUp->hover(pStep);

	for each (Player* player in _players)
		player->update(pStep);

	//if animation is done
	if (_curTime >= _totalTime)
	{
		for each (PickUp* pickUp in _pickups)
			pickUp->step();

		coolDowns();
		checkCollisions();

		_curTime -= _totalTime;
	}
}



void Level::applyAbility(Player* pPlayer)
{
	switch (pPlayer->getId())
	{
	case p4:
		Level::getBoard()->fireAbility(pPlayer->getBoardPos());
		break;

	case p2:
		Level::getBoard()->earthAbility(pPlayer->getBoardPos());
		break;

	case p3:

		break;

	case p1:
		pPlayer->_movement->fireAbility(true);
		Level::get()->_windCooldown = 4;
		break;
	}
}

void Level::coolDowns()
{
	if (_windCooldown > 0)
	{
		_windCooldown--;

		if (_windCooldown == 0)
			for each (Player* player in _players)
				if (player->getId() == p1)
				{
					player->_movement->fireAbility(false);
					break;
				}
	}

	if (_waterCooldown > 0)
	{
		_waterCooldown--;

		if (_waterCooldown == 0)
			for each (Player* player in _players)
			{
				if (player->getId() == p3)
					continue;

				player->_movement->fireAbility(2.0f);
			}
	}
}

void Level::checkCollisions()
{
	for each (Player* player in _players)
	{
		if (_board->outOfBounds(player->getNextPos()))
		{
			player->_movement->cancelMove();
			player->_checked = true;
		}
	}

	for each (Player* player1 in _players)
	{
		if (player1->_checked)
			continue;

		for each (Player* player2 in _players)
		{
			if (player2->_checked || player1 == player2)
				continue;

			if (player1->getNextPos() == player2->getNextPos())
			{
				player1->_checked = true; player1->_movement->cancelMove();
				player2->_checked = true; player2->_movement->cancelMove();
				continue;
			}

			if (player1->getNextPos() == player2->getBoardPos())
			{
				if (player2->getNextPos() == player1->getBoardPos())
				{
					player1->_checked = true; player2->_checked = true;
					player1->_movement->jump(2);
					player2->_movement->jump(0.5f);
				}
				else
				{
					player1->_checked = true; player1->_movement->cancelMove();
				}
				continue;
			}
		}
	}
	for each (Player* player in _players)
		player->_checked = false;
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
	Player* player = new Player(pPlayerId, pBoardPos, _totalTime, _wait);
	player->setParent(this);
	_players.push_back(player);
}

void Level::spawnPickUp(PickUp* pPickUp)
{
	_pickups.push_back(pPickUp);
	pPickUp->setParent(this);
}

Level::~Level() { }