#pragma once

#include <glm.hpp>

#include "../network/DataType.hpp"

struct TestData
{
	float r;
	float g;
	float b;
	float a;

	void to_string()
	{
		printf("%d %d %d %d\n", r, g, b, a);
	}
};