#include "mge/behaviours/FireBehaviour.hpp"

#include "../game/Level.hpp"
#include "../game/Player.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "../game/Enums.hpp"

#include <algorithm>

FireBehaviour::FireBehaviour(Player* pPlayer, glm::vec2 pBoardPos, float pJumpHeight, float const pTime, float pWait)
	: PlayerBehaviour(pPlayer, pBoardPos, pJumpHeight, pTime, pWait)
{ }


void FireBehaviour::activateAbility() {
	if (_hasActivated) return;
	cout << "ACTIVATION" << endl;
	Level::getBoard()->setOwner(glm::vec2(1, 1), getPlayerId());
	glm::vec2 pos = getBoardPos();
	Board* board = Level::getBoard();
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (board->getOwnerOfTile(glm::vec2(pos.x + i, pos.y + j)) != Id::empty) {
				cout << "tile set to color" << endl;
				board->setOwner(glm::vec2(pos.x + i, pos.y + j ), getPlayerId());
			}
		}
	}
	_hasActivated = true;


}

FireBehaviour::~FireBehaviour()
{
	//dtor
}