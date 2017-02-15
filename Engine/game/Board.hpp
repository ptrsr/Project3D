#ifndef BOARD_H
#define BOARD_H

#include "../game/Tile.hpp"
#include "../game/Enums.hpp"
class Board
{
	
public:
	static Board* get();
	static bool outOfBounds(glm::vec2);

	static void setOwner(glm::vec2 boardPos, Id player);
	static int getScore(Id pPlayerId);

	~Board();

private:

	Board();

	static Board* _board;

	glm::vec2 _size = glm::vec2(9, 9);

	Tile* _boardArray[9][9];

	void initializeBoard();

	//Singleton
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;

};
#endif