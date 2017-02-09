#pragma once

#include <glm.hpp>

#include "../network/Data.hpp"

struct TileData : public Data
{
	int xGrid;
	int zGrid;
	glm::vec3 color;
};