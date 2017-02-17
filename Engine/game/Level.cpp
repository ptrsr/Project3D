#include "../game/Level.hpp"

#include "../network/Client.hpp"
#include "../network/Server.hpp"

#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

#include "Enums.hpp"
#include "PickUps/ScoreCube.hpp"

Level* Level::_level;

Level::Level() :GameObject("level")
{
	//setLocalPosition(glm::vec3(-8.5f, 0, 0));

	spawnPickUp(new ScoreCube());

	_spawnPos.push_back(make_pair<int, int>(0, 0));
	_spawnPos.push_back(make_pair<int, int>(0, 8));
	_spawnPos.push_back(make_pair<int, int>(8, 8));
	_spawnPos.push_back(make_pair<int, int>(8, 0));

	_board = new Board();
	_board->setParent(this);
	World::add(this);

	_moveTime = 0.55f;
	_totalTime = 0.8f;
}

Level* Level::get()
{
	if (!_level)
		_level = new Level();

	return _level;
}

void Level::Host()
{
	SetupLevel(); //Reset the board

	_server = new Server(8888, 3); //Create a server
	thread server(&Server::StartServer, _server); //Create a thread for the server
	server.detach(); //Let it run seperately from the main thread

	pair<int, int> spawnPos = GetSpawnPosition(Id::p1);
	spawnPlayer(Id::p1, glm::vec2(spawnPos.first, spawnPos.second), true); //Spawn player
}

void Level::Join(const char* IP, int port)
{
	SetupLevel(); //Reset the board

	_client = new Client(); //Create a client
	thread client(&Client::Connect, _client, IP, port); //Create a thread for the client
	client.detach(); //Let it run seperately from the main thread
}

void Level::SetupLevel()
{
	_board->ResetBoard(); //Reset the board

	RemovePlayers(); //Reset the players
}

Player* Level::getPlayer(Id playerId)
{
	std::vector<Player*> players = Level::get()->getPlayers();

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->getId() == playerId)
			return players[i]; //Return player with matching id
	}

	return NULL; //No player with that id found
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

pair<int, int> Level::GetSpawnPosition(Id playerId)
{
	return _spawnPos[playerId - 1];
}

void Level::AddSpawn(Player* player)
{
	_spawnQueue.push_back(player);
}

void Level::update(float pStep)
{
	//if (_spawnQueue.size() > 0)
	//{
	//	Player* player = _spawnQueue[0];
	//	SpawnPlayer(player->getId(), player->getBoardPos(), _players.size() == 0 ? true : false);
	//	_spawnQueue.erase(_spawnQueue.begin());
	//	delete player;
	//}

	_curTime += pStep;

	//check for player input
	for each (Player* player in _players)
		player->_movement->checkKeys();

	//if player is moving
	if (_curTime < _moveTime)
	{
		for each (Player* player in _players)
			player->_movement->move(pStep + _deltaTime, _curTime, _moveTime, _lastMoveTime);

		_deltaTime = 0;
		_lastMoveTime = _curTime;
	}
	//if move ended
	else if (_lastMoveTime != 0)
	{
		for each (Player* player in _players)
		{
			//finish player animation
			player->_movement->finishMove(_moveTime, _lastMoveTime);

			//set tiles to new owner
			_board->setOwner(player->getBoardPos(), player->getId());

			//apply pickups
			for each (PickUp* pickUp in _pickups)
				if (pickUp->getBoardPos() == player->getBoardPos())
					pickUp->applyPickUp(player);
		}
		_lastMoveTime = 0;
	}

	//if animation is done
	if (_curTime >= _totalTime)
	{
		//set next move direction to desired direction
		for each (Player* player in _players)
			player->_movement->setDirection();

		checkCollisions();

		//pickup spawning countdown
		for each (PickUp* pickUp in _pickups)
			pickUp->step();

		//reset time for next step
		_curTime -= _totalTime;
		_deltaTime = _curTime;
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

void Level::RemovePlayers()
{
	for (int i = _players.size() - 1; i > 0; i--)
	{
		delete _players[i];
		_players.pop_back();
	}
}

void Level::spawnPlayer(Id pPlayerId, glm::vec2 pBoardPos, bool controlled)
{
	for each (Player* player in _players)
	{
		if (player->getId() == pPlayerId)
		{
			std::cout << "Error: Player already exists" << std::endl;
			return;
		}
	}
	Player* player = new Player(pPlayerId, pBoardPos, controlled);
	player->setParent(this);
	_players.push_back(player);
}

void Level::spawnPickUp(PickUp* pPickUp)
{
	_pickups.push_back(pPickUp);
	pPickUp->setParent(this);
}

Level::~Level() { }