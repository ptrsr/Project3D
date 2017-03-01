#ifndef EARTHBEHAVIOUR_H
#define EARTHBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/behaviours/PlayerBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"

class Player;

class EarthBehaviour : public PlayerBehaviour
{

	public:
		EarthBehaviour(Player* pPlayer, glm::vec2 boardPos, float pJumpHeight, float pTime, float pWait);
		virtual ~EarthBehaviour();

		virtual void update(float pStep) { };
		virtual void activateAbility();

		void message(sendMsg::Message) { };
};

#endif // ROTATINGBEHAVIOUR_H
