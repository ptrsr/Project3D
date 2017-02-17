#ifndef LEVEL_H
#define LEVEL_H


#include <iostream>
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/config.hpp"

#include "Player.hpp"
#include "PickUps\PickUp.hpp"
#include "Board.hpp"

class Client;
class Server;

class Level : public GameObject
{
public:
	~Level();

	static Level* get();
	static Player*				getPlayer(Id playerId);
	static std::vector<Player*> getPlayers();
	static std::vector<PickUp*> getPickUps();
	static Board*				getBoard();

	void Host();
	void Join(const char* IP, int port);

	virtual void update(float pStep);

	static bool checkAvailable(Player* pPlayer);

	void SetupLevel();
	pair<int, int> GetSpawnPosition(Id playerId);
	void AddSpawn(Player* player);
private:
	static Level* _level;

	void RemovePlayers();
	void spawnPlayer(Id, glm::vec2 pBoardPos, bool controlled);
	void spawnPickUp(PickUp* pPickUp);
	
	void checkCollisions();

	Client* _client;
	Server* _server;

	std::vector<Player*> _spawnQueue;
	std::vector<Player*> _players;
	std::vector<PickUp*> _pickups;
	Board* _board;
	std::vector<pair<int, int>> _spawnPos;

	float _curTime;
	float _deltaTime;
	float _lastMoveTime;
	float _totalTime;
	float _moveTime;

	glm::vec2 _size;

	Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
};
#endif