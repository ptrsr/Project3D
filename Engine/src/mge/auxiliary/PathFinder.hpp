#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../game/Tile.hpp"
#include <vector>

class PathFinder
{
public:
	PathFinder();
	~PathFinder();

	static vector<Tile*> findPath(Tile* pStartNode, Tile* pEndNode);
	static bool canReach(Tile* pStartNode, Tile* pEndNode);

private:
	static PathFinder* _pathFinder;

	Tile* _startNode;
	Tile* _endTile;
	Tile* _currentTile;

	vector<Tile*> _todoList;
	vector<Tile*> _doneList;

	vector<Tile*> _lastPath;

	bool _done;

	static PathFinder* get();

	void step();
	bool setTileCosts(Tile* pParentTile);
	void generatePath();

	PathFinder(const PathFinder&) = delete;
	PathFinder& operator=(const PathFinder&) = delete;
};

#endif // ! PATHFINDER_H
