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
	static std::vector<PickUp*> getPickUps();
	static Board*				getBoard();

	virtual void update(float pStep);

	static void step(Player* pPlayer);
	static bool outOfBounds(glm::vec2 pBoardPos);

private:
	static Level* _level;

	void spawnPlayer(Id, glm::vec2 pBoardPos);
	void spawnPickUp(PickUp* pPickUp);
	
	std::vector<Player*> _players;
	std::vector<PickUp*> _pickups;
	Board* _board;

	float _curTime;
	float _totalMoveTime = config::TOTAL_MOVE_TIME;
	glm::vec2 _size;

	Level();

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;
};
#endif