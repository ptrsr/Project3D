#pragma once

#include <glm.hpp>

#include "../network/Data.hpp"

class PlayerData : public Data
{
public:
	PlayerData(glm::mat4 transform);
	virtual ~PlayerData();

	glm::mat4 Transform;
};