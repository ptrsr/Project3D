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

class Level : public GameObject
{
public:
	~Level();

	static Level* get();
	static std::vector<Player*> getPlayers();
	static Player*				getPlayer(Id pPlayerId);
	static std::vector<PickUp*> getPickUps();
	static Board*				getBoard();
	static void					reset();
	static void					applyPickUp(Player* pPlayer);
	static void					applyAbility(Player* pPlayer);
	static void					moveDone();

	virtual void update(float pStep);

	static bool checkAvailable(Player* pPlayer);

private:
	static Level* _level;

	void spawnPlayer(Id, glm::vec2 pBoardPos);
	void spawnPickUp(PickUp* pPickUp);
	

	void coolDowns();
	void checkCollisions();

	std::vector<Player*> _players;
	std::vector<PickUp*> _pickups;
	Board* _board;

	//timing settings
	float _totalTime = 0.8f;
	float _wait		 = 0.5f;

	//time variable
	float _curTime;

	glm::vec2 _size;

	//player abilities
	int _waterCooldown = 0;
	int _windCooldown  = 0;

	bool checkAreas = false;

	Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
};
#endif