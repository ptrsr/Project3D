#pragma once

class Data
{
public:
	int empty;

	Data() { }
	virtual ~Data() { }

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(empty);
	}
};