#ifndef BREATHFIRST_H
#define BREATHFIRST_H

#include "../game/Tile.hpp"

class BreathFirst
{
public:
	BreathFirst();
	void disconnect(Tile* pTile);

private:
	vector<Tile*> _todoList;
	vector<Tile*> _doneList;

};





#endif // !BREATHFIRST_H
