#pragma once

#include <glm.hpp>

#include "../network/Data.hpp"

struct PlayerData : public Data
{
	glm::mat4 transform;

	PlayerData() : transform(glm::mat4(0)) { }
	explicit PlayerData(glm::mat4 pTransform) : transform(pTransform) { }

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Data>(this), transform);
	}
};