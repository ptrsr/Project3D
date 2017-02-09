#pragma once

struct Data
{
	int empty;

	Data() : empty(0) { }
	explicit Data(int pEmpty) : empty(pEmpty) { }

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(empty);
	}
};