#ifndef SCORECUBE_H
#define SCORECUBE_H

#include "PickUp.hpp"

class ScoreCube : public PickUp
{
public:
	ScoreCube(std::vector<MovementBehaviour*> pPlayers);

	virtual void applyPickUp(MovementBehaviour* pPlayer);
private:

};

#endif