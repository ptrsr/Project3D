#include "PathFinder.hpp"

#include <algorithm>

PathFinder* PathFinder::_pathFinder;

PathFinder::PathFinder()
{

}

bool compare(Tile* a, Tile* b)
{
	return a->costCurrent + a->costEstimate < b->costCurrent + b->costEstimate;
}

vector<Tile*> PathFinder::findPath(Tile* pStartNode, Tile* pEndNode)
{
	PathFinder* pathFinder = PathFinder::get();

	vector<Tile*> path;

	if (!pStartNode || !pEndNode)
		return path;

	pathFinder->_done = false;

	pathFinder->_doneList.clear();
	pathFinder->_todoList.clear();

	pathFinder->_startNode = pStartNode;
	pathFinder->_endTile   = pEndNode;

	pathFinder->_todoList.push_back(pStartNode);

	while (!pathFinder->_done)
		pathFinder->step();

	return pathFinder->_lastPath;
}

PathFinder* PathFinder::get()
{
	if (!_pathFinder)
		_pathFinder = new PathFinder();

	return _pathFinder;
}

void PathFinder::generatePath() 
{
	_lastPath.empty();

	Tile* tile = _endTile;

	while (tile != NULL) 
	{
		tile->getMaterial()->setColor(glm::vec3(1, 1, 0));
		_lastPath.push_back(_endTile);
		tile = tile->parent;
	}

	std::reverse(_lastPath.begin(), _lastPath.end());
}

void PathFinder::step()
{
	if (_done || _startNode == NULL || _endTile == NULL || _todoList.size() == 0) {

		_done = true;
		return;
	}

	//get a node from the open list
	_currentTile = _todoList[0];
	_todoList.erase(_todoList.begin());

	//and move that node to the closed list (one way or another, we are done with it...)
	_doneList.push_back(_currentTile);

	_currentTile->getMaterial()->setColor(glm::vec3(1, 1, 0));

	//is this our node? yay done...
	if (_currentTile == _endTile)
	{
		generatePath();
		_done = true;
	}
	else {
		//get all children and process them
		for each (Tile* tile in _currentTile->getConnections())
		{
			if (tile->getOwner() == _startNode->getOwner() && std::find(_doneList.begin(), _doneList.end(), tile) == _doneList.end() && setTileCosts(tile))
			{
				tile->parent = _currentTile;

				if (std::find(_todoList.begin(), _todoList.end(), tile) == _todoList.end())
					_todoList.push_back(tile);
			}
		}
		std::sort(_todoList.begin(), _todoList.end(), compare);
	}
}

bool PathFinder::setTileCosts(Tile* newTile)
{
	float costCurrent = glm::distance(_currentTile->getBoardPos(), newTile->getBoardPos()) + _currentTile->costCurrent;
	float costEstimate = glm::distance(_endTile->getBoardPos(), newTile->getBoardPos());

	if (newTile->parent == NULL || (newTile->costCurrent + newTile->costEstimate) > (costCurrent + costEstimate))
	{
		newTile->costCurrent = costCurrent;
		newTile->costEstimate = costEstimate;
		return true;
	}
	return false;
}



PathFinder::~PathFinder()
{

}