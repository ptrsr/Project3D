#pragma once

#include <glm.hpp>

#include "../network/Data.hpp"

struct PlayerData : public Data
{
	glm::mat4 transform;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Data>(this), transform);
	}
};