#ifndef PICKUP_H
#define PICKUP_H

#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/materials/LitMaterial.hpp"

#include <vector>

class PickUp : public GameObject
{
public:
	LitMaterial* _material;
	std::vector<MovementBehaviour*> _players;

	PickUp(std::string name, std::vector<MovementBehaviour*> pPlayers);
	~PickUp();

	static std::vector<PickUp*> getPickUps();

	virtual inline void update(float pStep) { };
	virtual void applyPickUp(MovementBehaviour* pPlayer) = 0;

	void spawn();

	glm::vec2 getBoardPos();

private:
	static std::vector<PickUp*> _pickUps;

	float _minDelay;
	float _maxDelay;

	glm::vec2 _boardPos;

};

#endif