#pragma once

class Data
{
public:
	Data();
	virtual ~Data();

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive();
	}
};