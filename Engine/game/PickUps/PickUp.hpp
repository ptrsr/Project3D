#ifndef PICKUP_H
#define PICKUP_H

#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "../game/Player.hpp"

#include <vector>

class PickUp : public GameObject
{
public:
	LitMaterial* _material;

	PickUp(std::string name, float moveTime);
	~PickUp();

	virtual inline void update(float pStep) { };
	virtual void applyPickUp(Player* pPlayer) = 0;

	virtual void step();

	void hover(float pStep);

	glm::vec2 getBoardPos();


protected:
	void reset();

	int _minDelay = 0;
	int _maxDelay = 0;


private:
	void spawn();

	float _countDown = 0;
	float _floatTimer = 0;

	float _spawnHeight = 7;

	float _moveTime;
	float _hoverDif = 0.4f;
	float _hoverHeight = 1.2f;

	glm::vec2 _boardPos;

};

#endif