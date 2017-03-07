#pragma once

#include "PickUp.hpp"

class Splash : public PickUp
{
public:
	Splash(float moveTime);

	virtual glm::vec2 applyPickUp(Player* pPlayer);
private:

};