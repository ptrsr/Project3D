#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include "mge/core/World.hpp"
#include "mge/core/GameObject.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/scenes/menuStates/LobbyState.hpp"
#include "mge/config.hpp"

#include "Player.hpp"
#include "PickUps\PickUp.hpp"
#include "Board.hpp"

#include "../network/packets/DataType.hpp"
#include "../network/packets/PlayerData.hpp"
#include "../network/packets/MoveData.hpp"
#include "../network/packets/PickupData.hpp"
#include "../network/packets/ScoreData.hpp"
#include "../network/packets/EffectData.hpp"
#include "../network/packets/StoreData.hpp"
#include "../network/packets/LeaveData.hpp"

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
	bool						checkIfFinished();
	float						getScoreOfId(int index);

	void Host();
	void Join(const char* IP, int port);
	
	virtual void update(float pStep);

	static bool checkAvailable(Player* pPlayer);
	
	void SetupLevel();
	pair<int, int> GetSpawnPosition(Id playerId);
	
	Client* GetClient();
	Server* GetServer();
	LobbyState* GetLobbyState();

	void Start(bool value);
	bool GetStart();
	void AddSpawn(PlayerData player);
	void AddMove(MoveData move);
	void AddPickUp(PickupData pickUp);
	void AddScore(ScoreData score);
	void AddEffect(EffectData effect);
	void AddStore(StoreData store);
	void AddLeave(LeaveData leave);

	void spawnPickUp(Effect type, glm::vec2 pos);
	void removePickUp(glm::vec2 pos);

	void CreatePacket(Id playerId, Dir dir, glm::vec2 pos); //Create Player packet
	void CreatePacket(Effect type, glm::vec2 pos, glm::vec2 oldPos); //Create PickUp packet
	void CreatePacket(Id playerId, int score); //Create Score packet
	void CreatePacket(Id playerId, Effect effect, glm::vec2 pos); //Create Effect packet
	void CreatePacket(Id playerId, Effect pickUp); //Create Store packet
	void CreatePacket(Id playerId); //Create Use packet
	void CreatePacket(Id playerId, bool value); //Create Ready packet

	void SendMoveData();
private:
	static Level* _level;

	void RemovePlayers();
	void spawnPlayer(Id, glm::vec2 pBoardPos, bool controlled);
	void spawnPickUp();

	void checkCollisions();

	void Send(DataType type, char* data);
	
	std::vector<Player*> _players;
	std::vector<PickUp*> _pickups;
	Board* _board;

	Client* _client = NULL;
	Server* _server = NULL;
	
	std::vector<pair<int, int>> _spawnPos;
	
	std::vector<PlayerData> _spawnQueue;
	std::vector<MoveData> _moveQueue;
	std::vector<PickupData> _pickUpQueue;
	std::vector<ScoreData> _scoreQueue;
	std::vector<EffectData> _effectQueue;
	std::vector<StoreData> _storeQueue;
	std::vector<LeaveData> _leaveQueue;
	
	bool _start = false;
	bool _send = false;
	bool _finished = false;

	GameObject* _fireStatue;
	GameObject* _earthStatue;
	GameObject* _waterStatue;
	GameObject* _windStatue;
	LobbyState * _lobbyState = NULL;


	float _currentScore[4] = { 1.01f,0.01f,0.01f,0.01f };
	
	//timing settings
	float _totalTime = 0.8f;
	float _wait		 = 0.5f;

	//time variable
	float _curTime = 0;

	glm::vec2 _size;

	Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
};
#endif