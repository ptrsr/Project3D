#pragma once

#include "../game/Enums.hpp"

struct MoveData
{
	Id playerId;
	Dir direction;
	int toBoardX;
	int toBoardY;
};