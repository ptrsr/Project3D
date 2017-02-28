#ifndef LEVEL_H
#define LEVEL_H


#include <iostream>
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/config.hpp"

#include "Player.hpp"
#include "PickUps/PickUp.hpp"
#include "Board.hpp"

#include "../network/packets/DataType.hpp"
#include "../network/packets/MoveData.hpp"
#include "../network/packets/PickupData.hpp"
#include "../network/packets/ScoreData.hpp"

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

	void Start(bool value);
	void AddSpawn(Player* player);
	void AddMove(MoveData move);
	void AddPickUp(PickupData pickUp);
	void AddScore(ScoreData score);

	void spawnPickUp(PickUp* pPickUp, glm::vec2 pos);
	void removePickUp(glm::vec2 pos);

	void CreatePacket(DataType type);
	void CreatePacket(glm::vec2 pos, glm::vec2 oldPos);
	void CreatePacket(Id playerId, int score);
private:
	static Level* _level;

	void RemovePlayers();
	void spawnPlayer(Id, glm::vec2 pBoardPos, bool controlled);
	void spawnPickUp(PickUp* pPickUp);

	void Send(DataType type, char* data);
	
	void checkCollisions();

	Client* _client = NULL;
	Server* _server = NULL;

	bool _start = false;

	float _curTime = 0;
	float _deltaTime = 0;
	float _lastMoveTime = 0;
	float _totalTime = 0;
	float _moveTime = 0;

	std::vector<Player*> _spawnQueue;
	std::vector<MoveData> _moveQueue;
	std::vector<PickupData> _pickUpQueue;
	std::vector<ScoreData> _scoreQueue;
	std::vector<Player*> _players;
	std::vector<PickUp*> _pickups;
	Board* _board;
	std::vector<pair<int, int>> _spawnPos;

	glm::vec2 _size;

	Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
};
#endif