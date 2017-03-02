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

	pair<int, int> spawnPos = GetSpawnPosition(Id::p1);
	spawnPlayer(Id::p1, glm::vec2(spawnPos.first, spawnPos.second), true); //Spawn player

	_server = new Server(8888, 3); //Create a server
	thread server(&Server::StartServer, _server); //Create a thread for the server
	server.detach(); //Let it run seperately from the main thread
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

void Level::Start(bool value)
{
	_start = value;
}

void Level::AddSpawn(Player* player)
{
	_spawnQueue.push_back(player);
}

void Level::AddMove(MoveData move)
{
	_moveQueue.push_back(move);
}

void Level::AddPickUp(PickupData pickUp)
{
	_pickUpQueue.push_back(pickUp);
}

void Level::AddScore(ScoreData score)
{
	_scoreQueue.push_back(score);
}

void Level::CreatePacket(DataType type)
{
	for (int i = 0; i < _players.size(); i++)
	{
		if (_server != NULL || _client != NULL && i == (_client->GetId() - 1))
		{
			switch (type)
			{
			case TIMEDATA:
				TimeData td;
				td.curTime = _curTime;
				td.deltaTime = _deltaTime;
				td.lastMoveTime = _lastMoveTime;
				td.totalTime = _totalTime;
				td.moveTime = _moveTime;
				Send(type, (char*)&td);
				break;
			case MOVEDATA:
				MoveData md;
				md.playerId = _players[i]->getId();
				md.direction = _players[i]->_movement->GetDDir();
				Send(type, (char*)&md);
				break;
			case SCOREDATA:
				break;
			case TILEDATA:
				break;
			}
		}
	}
}

void Level::CreatePacket(Id playerId, Dir dir)
{
	MoveData md;
	md.playerId = playerId;
	md.direction = dir;

	Send(DataType::MOVEDATA, (char*)&md);
}

void Level::CreatePacket(glm::vec2 pos, glm::vec2 oldPos)
{
	PickupData pd;
	pd.boardX = pos.x;
	pd.boardY = pos.y;
	pd.oldX = oldPos.x;
	pd.oldY = oldPos.y;
	Send(DataType::PICKUPDATA, (char*)&pd);
}

void Level::CreatePacket(Id playerId, int score)
{
	ScoreData sd;
	sd.playerId = playerId;
	sd.score = score;

	Send(DataType::SCOREDATA, (char*)&sd);
}

void Level::Send(DataType type, char* data)
{
	if (_client != NULL)
		_client->Send(type, data);
	if (_server != NULL)
		_server->SendAll(type, data);
}

void Level::update(float pStep)
{
	//
	// - Server tells where the clients are going
	// - Add time stamp to data packets
	// - Send Move packets frame-independent
	// - More testing with 4 players
	// - Clean up queues
	// - Handle client/host leaving
	// - Remember to set client/server to NULL on leaving
	//
	while (_spawnQueue.size() > 0)
	{
		Player* player = _spawnQueue[0];
		spawnPlayer(player->getId(), player->getBoardPos(), player->IsControlled());
		_spawnQueue.erase(_spawnQueue.begin());
		delete player;
	}
	while (_moveQueue.size() > 0)
	{
		MoveData move = _moveQueue[0];
		_players[move.playerId - 1]->_movement->SetDDir(move.direction);

		//Player* player = getPlayers()[move.playerId - 1];
		//player->_movement->SetDDir(move.direction);
		//player->setLocalPosition(glm::vec3(move.toBoardX, 0.5f, move.toBoardY));

		_moveQueue.erase(_moveQueue.begin());
	}
	while (_pickUpQueue.size() > 0)
	{
		PickupData pData = _pickUpQueue[0];
		removePickUp(glm::vec2(pData.oldX, pData.oldY));
		if (pData.boardX != -1 && pData.boardY != -1)
			spawnPickUp(new ScoreCube(), glm::vec2(pData.boardX, pData.boardY));
		_pickUpQueue.erase(_pickUpQueue.begin());
	}

	if (!_start)
		return;

	if (_server != NULL && _pickups.size() == 0)
		spawnPickUp(new ScoreCube()); //Spawn the score cube

	_curTime += pStep;

	if (_curTime < 0.65f)
	{
		_send = false;
		//check for player input
		for each (Player* player in _players)
			player->_movement->checkKeys();
	}
	else
	{
		//if (!_send)
		//{
			if (_server != NULL)
				CreatePacket(Id::p1, _players[0]->_movement->GetDDir());
			if (_client != NULL)
				CreatePacket(_client->GetId(), _players[_client->GetId() - 1]->_movement->GetDDir());
		//}
		//_send = true;
		//if (!_send)
			//CreatePacket(_server != NULL ? Id::p1 : _client->GetId(), _server != NULL ? _players[0]->_movement->GetDDir() : _players[_client->GetId() - 1]->_movement->GetDDir());
		//_send = true;
	}

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

			if (_server != NULL)
			{
				//apply pickups
				for each (PickUp* pickUp in _pickups)
					if (pickUp->getBoardPos() == player->getBoardPos())
					{
						glm::vec2 oldPos = pickUp->applyPickUp(player);
						CreatePacket(pickUp->getBoardPos(), oldPos);
					}
			}
		}
		_lastMoveTime = 0;
	}
		

	//if animation is done
	if (_curTime >= _totalTime)
	{
		while (_scoreQueue.size() > 0)
		{
			ScoreData sData = _scoreQueue[0];
			_players[sData.playerId - 1]->addScore(sData.score); //Add player score
			_board->getScore(sData.playerId); //Clean player line
			_scoreQueue.erase(_scoreQueue.begin());
		}

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

void Level::spawnPickUp(PickUp* pPickUp, glm::vec2 pos)
{
	_pickups.push_back(pPickUp);
	pPickUp->setParent(this);
	pPickUp->spawn(pos);
}

void Level::removePickUp(glm::vec2 pos)
{
	for (int i = 0; i < _pickups.size(); i++)
	{
		if (_pickups[i]->getBoardPos() == pos)
		{
			delete _pickups[i];
			_pickups.erase(_pickups.begin() + i);
			return;
		}
	}
}

Level::~Level() { }