#include "../game/Level.hpp"

#include "../network/Client.hpp"
#include "../network/Server.hpp"

#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "mge/auxiliary/ObjectCache.hpp"
#include "mge/materials/StatueMaterial.hpp";
#include "Enums.hpp"
#include "PickUps/ScoreCube.hpp"
#include "PickUps/Splash.hpp"
#include "PickUps/Speed.hpp"
#include "PickUps/Slow.hpp"

Level* Level::_level;

Level::Level() :GameObject("level")
{
	setLocalPosition(glm::vec3(-8.5f, 0, 0.5f));

	_spawnPos.push_back(make_pair<int, int>(0, 0));
	_spawnPos.push_back(make_pair<int, int>(0, 8));
	_spawnPos.push_back(make_pair<int, int>(8, 8));
	_spawnPos.push_back(make_pair<int, int>(8, 0));

	_board = new Board();
	_board->setParent(this);

	_fireStatue = ObjectCache::find("Fire1");
	_earthStatue = ObjectCache::find("Earth1");
	_waterStatue = ObjectCache::find("Water1");
	_windStatue = ObjectCache::find("Wind1");

	_fireStatue->setMaterial(new StatueMaterial(nullptr, glm::vec3(1, 0, 0)));
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
					glm::vec2 oldPos = pickUp->applyPickUp(pPlayer);
					CreatePacket(pickUp->GetType(), pickUp->getBoardPos(), oldPos);
				}
		//Add pickup to delete list
	}
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

	//Wait till all players are ready
	if (!_start)
		return;
	
	//Spawns random pick up
	if (_server != NULL && _pickups.size() < 2)
	{
		spawnPickUp();
	}

	_curTime += pStep;

	if (_curTime < 0.65f) //Wait for cube to land
	{
		_send = false;
	}
	else
	{
		if (!_send)
		{
			//Send move data
			if (_server != NULL)
				CreatePacket(Id::p1, _players[0]->_movement->GetDDir(), _players[0]->_movement->getBoardPos());
			if (_client != NULL)
				CreatePacket(_client->GetId(), _players[_client->GetId() - 1]->_movement->GetDDir(), _players[_client->GetId() - 1]->getBoardPos());
		}
		_send = true;

		while (_moveQueue.size() > 0)
		{
			MoveData move = _moveQueue[0];

			Player* player = getPlayers()[move.playerId - 1];
			player->_movement->SetDDir(move.direction);
			player->setBoardPos(glm::vec2(move.boardX, move.boardY));

			_moveQueue.erase(_moveQueue.begin());
		}
		while (_scoreQueue.size() > 0)
		{
			ScoreData sData = _scoreQueue[0];
			_board->getScore(sData.playerId);
			_players[sData.playerId - 1]->addScore(sData.score);
			_scoreQueue.erase(_scoreQueue.begin());
		}
		while (_effectQueue.size() > 0)
		{
			EffectData eData = _effectQueue[0];
			switch (eData.effect)
			{
			case Effect::splash:
				_board->splash(eData.playerId, glm::vec2(eData.boardX, eData.boardY));
				break;
			}
			_effectQueue.erase(_effectQueue.begin());
		}
	}


	if (_finished) return;
	Id hightestScorePlayer = _board->getPlayerWithHighestScore();

	if (hightestScorePlayer != -1)
	{
		_currentScore[hightestScorePlayer] += pStep;
		((StatueMaterial*)_fireStatue->getMaterial())->setScore(_currentScore[hightestScorePlayer] / 30.0f);
		if (_currentScore[hightestScorePlayer] == 30.0f) {

			_finished = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
		_finished = true;
	}

	
	for each (PickUp* pickUp in _pickups)
		pickUp->hover(pStep);

	for each (Player* player in _players)
		player->update(pStep);

	//If animation is done
	if (_curTime >= _totalTime)
	{
		for each (PickUp* pickUp in _pickups)
			pickUp->step();

		coolDowns();
		checkCollisions();

		_curTime -= _totalTime;
	}
}

bool Level::checkIfFinished() {
	return _finished;
}

float Level::getScoreOfId(int index) {
	return _currentScore[index];
}

void Level::applyAbility(Player* pPlayer)
{
	switch (pPlayer->getId())
	{
	case p4:
		//Level::getBoard()->fireAbility(pPlayer->getBoardPos());
		break;

	case p2:
		//Level::getBoard()->earthAbility(pPlayer->getBoardPos());
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
	Player* player = new Player(pPlayerId, pBoardPos, _totalTime, _wait, controlled);
	player->setParent(this);
	_players.push_back(player);
}

void Level::spawnPickUp()
{
	PickUp* pickUp;

	pickUp = new Splash(_totalTime);

	_pickups.push_back(pickUp);
	pickUp->setParent(this);
}

void Level::spawnPickUp(Effect type, glm::vec2 pos)
{
	PickUp* pickUp;

	switch (type)
	{
	case splash:
		pickUp = new Splash(_totalTime);
		break;
	case speed:
		break;
	case slow:
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