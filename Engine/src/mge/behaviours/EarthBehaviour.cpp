#include "mge/behaviours/EarthBehaviour.hpp"

#include "../game/Level.hpp"
#include "../game/Player.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "../game/Enums.hpp"

#include <algorithm>

EarthBehaviour::EarthBehaviour(Player* pPlayer, glm::vec2 pBoardPos, float pJumpHeight, float const pTime, float pWait)
	: PlayerBehaviour(pPlayer, pBoardPos, pJumpHeight, pTime, pWait)
{ }


void EarthBehaviour::activateAbility() {

}

EarthBehaviour::~EarthBehaviour()
{
	//dtor
}