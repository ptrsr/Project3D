#ifndef SPEEDUP_H
#define SPEEDUP_H

#include "PickUp.hpp"

class SpeedUp : public PickUp
{
public:
	SpeedUp(float moveTime);

	virtual void applyPickUp(Player* pPlayer);
private:

};

#endif