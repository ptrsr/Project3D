#include "BreathFirst.hpp"

#include <algorithm>

BreathFirst::BreathFirst()
{

}

void BreathFirst::disconnect(Tile* pTile)
{
	if (pTile->_connected == false)
		return;

	_todoList.push_back(pTile);

	while (_todoList.size() != 0)
	{
		Tile* tile = _todoList[0];
		
		tile->getMaterial()->setColor(glm::vec3(1, 1, 0));

		_todoList.erase(_todoList.begin());
		_doneList.push_back(tile);

		tile->_connected = false;

		for each (Tile* connectedTile in tile->getConnections())
			if (connectedTile->getOwner() == tile->getOwner() && std::find(_doneList.begin(), _doneList.end(), connectedTile) == _doneList.end())
				_todoList.push_back(connectedTile);
	}

	_todoList.clear();
	_doneList.clear();
}