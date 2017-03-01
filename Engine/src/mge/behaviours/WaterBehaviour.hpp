#ifndef WATERBEHAVIOUR_H
#define WATERBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include "mge/behaviours/PlayerBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"

class Player;

class WaterBehaviour : public PlayerBehaviour
{

	public:
		WaterBehaviour(Player* pPlayer, glm::vec2 boardPos, float pJumpHeight, float pTime, float pWait);
		virtual ~WaterBehaviour();

		virtual void update(float pStep) { };
		virtual void activateAbility();

		void message(sendMsg::Message) { };
};

#endif // ROTATINGBEHAVIOUR_H
