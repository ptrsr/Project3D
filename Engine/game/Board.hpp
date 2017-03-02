#ifndef BOARD_H
#define BOARD_H

#include "../game/Tile.hpp"
#include "../game/Enums.hpp"
class Board : public GameObject
{
	
public:
	Board();
	
	bool outOfBounds(glm::vec2);

	void setOwner(glm::vec2 pBoardPos, Id pPlayer);
	Id getOwnerOfTile(glm::vec2 boardPos);

	int getScore(Id pPlayerId);

	void fireAbility(glm::vec2 pBoardPos);
	void earthAbility(glm::vec2 pBoardPos);


private:
	glm::vec2 _size = glm::vec2(9, 9);

	Tile* _boardArray[9][9];

	void initializeBoard();
};
#endif