#include "mge/behaviours/WindBehaviour.hpp"

#include "../game/Level.hpp"
#include "../game/Player.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "../game/Enums.hpp"

#include <algorithm>

WindBehaviour::WindBehaviour(Player* pPlayer, glm::vec2 pBoardPos, float pJumpHeight, float const pTime, float pWait)
	: PlayerBehaviour(pPlayer, pBoardPos, pJumpHeight, pTime, pWait)
{ }


void WindBehaviour::activateAbility() {

}

WindBehaviour::~WindBehaviour()
{
	//dtor
}