#pragma once

#include "PickUp.hpp"

class Splash : public PickUp
{
public:
	Splash(float moveTime);

	virtual void applyPickUp(Player* pPlayer);
private:

};