#ifndef WINDBEHAVIOUR_H
#define WINDBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/behaviours/PlayerBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"

class Player;

class WindBehaviour : public PlayerBehaviour
{

	public:
		WindBehaviour(Player* pPlayer, glm::vec2 boardPos, float pJumpHeight, float pTime, float pWait);
		virtual ~WindBehaviour();

		virtual void update(float pStep) { };
		virtual void activateAbility();

		void message(sendMsg::Message) { };
};

#endif // ROTATINGBEHAVIOUR_H
