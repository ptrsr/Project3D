#pragma once

#include "../game/Enums.hpp"

struct PlayerData
{
	Id playerId;
	int boardX;
	int boardY;
	bool controlled;
};