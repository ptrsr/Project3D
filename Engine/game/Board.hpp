#ifndef BOARD_H
#define BOARD_H

#include "../game/Tile.hpp"
#include "../game/Enums.hpp"
class Board : public GameObject
{
	
public:
	Board();
	
	bool outOfBounds(glm::vec2);

	void setOwner(glm::vec2 boardPos, Id player);
	int getScore(Id pPlayerId);

private:
	glm::vec2 _size = glm::vec2(9, 9);

	Tile* _boardArray[9][9];

	void initializeBoard();
};
#endif