#include "../game/Level.hpp"

#include "../network/Client.hpp"
#include "../network/Server.hpp"

#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

#include "Enums.hpp"
#include "PickUps/Splash.hpp"
#include "PickUps/Speed.hpp"

Level* Level::_level;

Level::Level() :GameObject("level")
{
	srand(time(NULL));

	setLocalPosition(glm::vec3(-8.5f, 0, 0.5f));

	_spawnPos.push_back(make_pair<int, int>(0, 0));
	_spawnPos.push_back(make_pair<int, int>(0, 8));
	_spawnPos.push_back(make_pair<int, int>(8, 8));
	_spawnPos.push_back(make_pair<int, int>(8, 0));

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

void Level::Host()
{
	SetupLevel(); //Reset the board

	pair<int, int> spawnPos = GetSpawnPosition(Id::p1);
	spawnPlayer(Id::p1, glm::vec2(spawnPos.first, spawnPos.second), true); //Spawn player

	_server = new Server(56789, 3); //Create a server
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

void Level::reset()
{
	delete _level;
	_level = new Level();
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
		if (players[i] != NULL && players[i]->getId() == playerId)
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
		if (player == NULL || pPlayer == player)
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

Client* Level::GetClient()
{
	return _client;
}

Server* Level::GetServer()
{
	return _server;
}

void Level::Start(bool value)
{
	_start = value;
}

bool Level::GetStart()
{
	return _start;
}

void Level::AddSpawn(PlayerData player)
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

void Level::AddEffect(EffectData effect)
{
	_effectQueue.push_back(effect);
}

void Level::AddStore(StoreData store)
{
	_storeQueue.push_back(store);
}

void Level::AddLeave(LeaveData leave)
{
	_leaveQueue.push_back(leave);
}

void Level::CreatePacket(Id playerId, Dir dir, glm::vec2 pos)
{
	MoveData md;
	md.playerId = playerId;
	md.direction = dir;
	md.boardX = pos.x;
	md.boardY = pos.y;

	Send(DataType::MOVEDATA, (char*)&md);
}

void Level::CreatePacket(Effect type, glm::vec2 pos, glm::vec2 oldPos)
{
	PickupData pd;
	pd.type = type;
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

void Level::CreatePacket(Id playerId, Effect effect, glm::vec2 pos)
{
	EffectData ed;
	ed.playerId = playerId;
	ed.effect = effect;
	ed.boardX = pos.x;
	ed.boardY = pos.y;

	Send(DataType::EFFECTDATA, (char*)&ed);
	AddEffect(ed);
}

void Level::CreatePacket(Id playerId, Effect pickUp)
{
	StoreData sd;
	sd.playerId = playerId;
	sd.pickUp = pickUp;

	Send(DataType::STOREDATA, (char*)&sd);
}

void Level::CreatePacket(Id playerId)
{
	UseData ud;
	ud.playerId = playerId;

	Send(DataType::USEDATA, (char*)&ud);
}

void Level::SendMoveData()
{
	if (_server != NULL)
		CreatePacket(Id::p1, _players[0]->_movement->GetDDir(), _players[0]->_movement->getBoardPos());
	if (_client != NULL)
		CreatePacket(_client->GetId(), _players[_client->GetId() - 1]->_movement->GetDDir(), _players[_client->GetId() - 1]->getBoardPos());
}

void Level::Send(DataType type, char* data)
{
	if (_client != NULL)
		_client->Send(type, data);
	if (_server != NULL)
		_server->SendAll(type, data);
}

void Level::ApplyPickUp(Player* pPlayer)
{
	if (_server != NULL)
	{
		for each (PickUp* pickUp in Level::getPickUps())
			if (pickUp->getBoardPos() == pPlayer->getBoardPos())
				if (pickUp->getBoardPos() == pPlayer->getBoardPos())
				{
					pPlayer->StorePickUp(pickUp);

					//Send who picked it up
					CreatePacket(pPlayer->getId(), pickUp->GetType());

					//Delete pickup
					PickupData pd;
					pd.boardX - 1;
					pd.boardY = -1;
					pd.oldX = pickUp->getBoardPos().x;
					pd.oldY = pickUp->getBoardPos().y;
					AddPickUp(pd);

					CreatePacket(pickUp->GetType(), glm::vec2(-1,-1), pickUp->getBoardPos());
				}
	}
}

void Level::update(float pStep)
{
	//
	// - Clean up queues
	// - Handle client/host leaving
	// - Remember to set client/server to NULL on leaving
	//
	while (_leaveQueue.size() > 0)
	{
		LeaveData leave = _leaveQueue[0];
		_board->getScore(leave.playerId); //Reset all player's tiles
		delete _players[leave.playerId - 1]; //Delete player
		_players[leave.playerId - 1] = NULL; //Set value to NULL for future use
		_leaveQueue.erase(_leaveQueue.begin());
	}
	while (_spawnQueue.size() > 0)
	{
		PlayerData pData = _spawnQueue[0];
		spawnPlayer(pData.playerId, glm::vec2(pData.boardX, pData.boardY), pData.controlled);
		_spawnQueue.erase(_spawnQueue.begin());
	}
	while (_pickUpQueue.size() > 0)
	{
		PickupData pData = _pickUpQueue[0];
		removePickUp(glm::vec2(pData.oldX, pData.oldY));
		if (pData.boardX != -1 && pData.boardY != -1)
			spawnPickUp(pData.type, glm::vec2(pData.boardX, pData.boardY));
		_pickUpQueue.erase(_pickUpQueue.begin());
	}
	while (_scoreQueue.size() > 0)
	{
		ScoreData sData = _scoreQueue[0];
		_board->getScore(sData.playerId);
		_players[sData.playerId - 1]->addScore(sData.score);
		_scoreQueue.erase(_scoreQueue.begin());
	}
	while (_storeQueue.size() > 0)
	{
		StoreData sData = _storeQueue[0];
		Player* player = _players[sData.playerId - 1];
		switch (sData.pickUp)
		{
		case Effect::splash:
			player->StorePickUp(new Splash(0));
			break;
		case Effect::speed:
			player->StorePickUp(new Speed(0));
			break;
		}
		_storeQueue.erase(_storeQueue.begin());
	}
	while (_moveQueue.size() > 0)
	{
		MoveData move = _moveQueue[0];

		Player* player = getPlayers()[move.playerId - 1];
		player->_movement->SetDDir(move.direction);
		player->setBoardPos(glm::vec2(move.boardX, move.boardY));

		_moveQueue.erase(_moveQueue.begin());
	}

	//Wait till all players are ready
	if (!_start)
		return;
	
	//Spawns random pick up
	if (_server != NULL && _pickups.size() < 2)
	{
		spawnPickUp();
	}

	_curTime += pStep;
	
	for each (PickUp* pickUp in _pickups)
		pickUp->hover(pStep);

	for each (Player* player in _players)
	{
		if (player != NULL)
			player->update(pStep);
	}

	//If animation is done
	if (_curTime >= _totalTime)
	{
		for (int i = 0; i < _effectQueue.size(); i++)
		{
			EffectData eData = _effectQueue[0];
			switch (eData.effect)
			{
			case Effect::splash:
				_board->splash(eData.playerId, glm::vec2(eData.boardX, eData.boardY));
				break;
			case Effect::speed:
				if (_players[eData.playerId - 1]->_movement->SpeedActive())
					continue;

				_players[eData.playerId - 1]->_movement->activateSpeed();
				break;
			}
			_effectQueue.erase(_effectQueue.begin());
		}

		for each (PickUp* pickUp in _pickups)
			pickUp->step();

		checkCollisions();

		_curTime -= _totalTime;
	}
}

void Level::checkCollisions()
{
	for each (Player* player in _players)
	{
		if (player == NULL)
			continue;

		if (_board->outOfBounds(player->getNextPos()))
		{
			player->_movement->cancelMove();
			player->_checked = true;
		}
	}

	for each (Player* player1 in _players)
	{
		if (player1 == NULL || player1->_checked)
			continue;

		for each (Player* player2 in _players)
		{
			if (player2 == NULL || player2->_checked || player1 == player2)
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
	{
		if (player == NULL)
			continue;

		player->_checked = false;
	}
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
	//Id for a previously left player spot
	int spot = -1;

	for (int i = 0; i < _players.size(); i++)
	{
		if (_players[i] != NULL && _players[i]->getId() == pPlayerId)
		{
			std::cout << "ERROR: Player already exists" << std::endl;
			return;
		}
		if (_players[i] == NULL && pPlayerId - 1 == i)
		{
			spot = i;
			break;
		}
	}
	Player* player = new Player(pPlayerId, pBoardPos, _totalTime, _wait, controlled);
	player->setParent(this);

	if (spot == -1)
		_players.push_back(player);
	else
		_players[spot] = player;
}

//Server spawn function
void Level::spawnPickUp()
{
	PickUp* pickUp;

	int rng = rand() % 2;

	switch (rng)
	{
	case 0:
		pickUp = new Splash(_totalTime);
		break;
	case 1:
		pickUp = new Speed(_totalTime);
		break;
	}
	pickUp->reset();

	_pickups.push_back(pickUp);
	pickUp->setParent(this);
}

//Client spawn function
void Level::spawnPickUp(Effect type, glm::vec2 pos)
{
	PickUp* pickUp;

	switch (type)
	{
	case splash:
		pickUp = new Splash(_totalTime);
		break;
	case speed:
		pickUp = new Speed(_totalTime);
		break;
	}
	_pickups.push_back(pickUp);
	pickUp->setParent(this);
	pickUp->spawn(pos);
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