#pragma once

#include "../game/Enums.hpp"

struct PickupData
{
	Effect type;
	int boardX;
	int boardY;
	int oldX;
	int oldY;
};