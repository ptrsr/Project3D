#pragma once

#include "PickUp.hpp"

class Speed : public PickUp
{
public:
	Speed(float moveTime);

	virtual void applyPickUp(Player* pPlayer);
private:

};