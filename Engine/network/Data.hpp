#pragma once

struct Data
{
	int empty;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(empty);
	}
};