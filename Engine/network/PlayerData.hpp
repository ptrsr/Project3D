#pragma once

#include <glm.hpp>

#include "../network/Data.hpp"

class PlayerData : public Data
{
public:
	glm::mat4 transform;

	PlayerData() { }
	PlayerData(glm::mat4 pTransform) : transform(pTransform) { }

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Data>(this), transform);
	}
};