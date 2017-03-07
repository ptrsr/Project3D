#ifndef SCORECUBE_H
#define SCORECUBE_H

#include "PickUp.hpp"

class ScoreCube : public PickUp
{
public:
	ScoreCube(float moveTime);

	virtual glm::vec2 applyPickUp(Player* pPlayer);
private:

};

#endif