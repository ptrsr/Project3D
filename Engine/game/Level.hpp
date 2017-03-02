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
	static void					reset();
	void						ApplyPickUp(Player* pPlayer);
	static void					applyAbility(Player* pPlayer);

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
	void CreatePacket(Id playerId, Dir dir);
	void CreatePacket(glm::vec2 pos, glm::vec2 oldPos);
	void CreatePacket(Id playerId, int score);
	
private:
	static Level* _level;

	void RemovePlayers();
	void spawnPlayer(Id, glm::vec2 pBoardPos, bool controlled);
	void spawnPickUp(PickUp* pPickUp);

	void coolDowns();
	void checkCollisions();

	void Send(DataType type, char* data);
	
	std::vector<Player*> _players;
	std::vector<PickUp*> _pickups;
	Board* _board;

	Client* _client = NULL;
	Server* _server = NULL;
	
	std::vector<pair<int, int>> _spawnPos;
	
	std::vector<Player*> _spawnQueue;
	std::vector<MoveData> _moveQueue;
	std::vector<PickupData> _pickUpQueue;
	std::vector<ScoreData> _scoreQueue;
	
	bool _start = false;
	bool _send = false;
	
	//timing settings
	float _totalTime = 0.8f;
	float _wait		 = 0.5f;

	//time variable
	float _curTime = 0;

	glm::vec2 _size;

	//player abilities
	int _waterCooldown = 0;
	int _windCooldown  = 0;

	Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
};
#endif