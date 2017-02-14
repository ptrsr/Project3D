#include "../game/Level.hpp"
#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

#include "Enums.hpp"
#include "PickUps/ScoreCube.hpp"

Level::Level(glm::vec2 pSize) :GameObject("level")
{
	_size = pSize;
	_player = new Player(p1, glm::vec2(0));

	Board::get();
	PickUp* score = new ScoreCube();
}

Level::~Level()
{
	delete _player;
	delete Board::get();
}