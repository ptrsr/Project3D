#include "../game/Level.hpp"
#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

#include "Enums.hpp"
#include "PickUps/ScoreCube.hpp"

Level::Level(glm::vec2 pSize) :GameObject("level")
{
	std::vector<MovementBehaviour*> players;

	_size = pSize;
	Player* player1 = new Player(p1, glm::vec2(0)); players.push_back(player1->_movement);

	Board::get();
	PickUp* score = new ScoreCube(players);
}

Level::~Level()
{
	delete Board::get();
}