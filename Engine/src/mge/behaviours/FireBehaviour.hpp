#ifndef FIREBEHAVIOUR_H
#define FIREBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/behaviours/PlayerBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"

class Player;

class FireBehaviour : public PlayerBehaviour
{

	public:
		FireBehaviour(Player* pPlayer, glm::vec2 boardPos, float pJumpHeight, float pTime, float pWait);
		virtual ~FireBehaviour();

		virtual void update(float pStep) { };
		virtual void activateAbility();

		void message(sendMsg::Message) { };
};

#endif // ROTATINGBEHAVIOUR_H
