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
	//spawnPlayer(Id::p1, glm::vec2(0, 0));
	//spawnPickUp(new ScoreCube());

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
	_server = new Server(8888, 3); //Create a server
	thread server(&Server::StartServer, _server); //Create a thread for the server
	server.detach(); //Let it run seperately from the main thread

	SetupLevel(Id::p1);
}

void Level::Join(const char* IP, int port)
{
	_client = new Client(); //Create a client
	thread client(&Client::Connect, _client, IP, port); //Create a thread for the client
	client.detach(); //Let it run seperately from the main thread
}

void Level::SetupLevel(Id playerId)
{
	_board->ResetBoard(); //Reset the board

	RemovePlayers(); //Reset the players

	for (int i = 0; i < _server->ConnectedCount() + 4; i++)
	{
		Id id = static_cast<Id>(i + 1); //PlayerId
		spawnPlayer(id, glm::vec2(i, i), playerId == id ? true : false); //Spawn either a controlled or non-controlled player
	}
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

void Level::step(Player* pPlayer)
{
	Level* level = Level::get();

	level->_board->setOwner(pPlayer->getBoardPos(), pPlayer->getId());

	for each (PickUp* pickUp in level->_pickups)
		if (pPlayer->getBoardPos() == pickUp->getBoardPos())
			pickUp->applyPickUp(pPlayer);
}

bool Level::outOfBounds(glm::vec2 pBoardPos)
{
	return Level::get()->_board->outOfBounds(pBoardPos);
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
	World::add(player);
	_players.push_back(player);
}

void Level::spawnPickUp(PickUp* pPickUp)
{
	_pickups.push_back(pPickUp);
	pPickUp->setParent(this);
}

Level::~Level() { }