#include "../game/Level.hpp"
#include "../game/Player.hpp"
#include "Tile.hpp"
#include "Board.hpp"

#include "Enums.hpp"
#include "PickUps/ScoreCube.hpp"

Level::Level(glm::vec2 pSize) :GameObject("level")
{
	std::vector<Player*> players;

	_size = pSize;
	_player = new Player(p1, glm::vec2(0)); players.push_back((Player*)_player);

	Board::get();
	PickUp* score = new ScoreCube(players);
}

Level::~Level()
{
	delete _player;
	delete Board::get();
}