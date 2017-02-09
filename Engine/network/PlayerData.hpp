#pragma once

#include <glm.hpp>

struct PlayerData
{
	glm::mat4 transform;
	int paintedTiles[];
};