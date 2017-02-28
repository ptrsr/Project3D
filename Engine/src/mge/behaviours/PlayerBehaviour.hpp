#ifndef PLAYERBEHAVIOUR_H
#define PLAYERBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"

class Player;

class PlayerBehaviour : public AbstractBehaviour
{

	public:
		PlayerBehaviour(Player* pPlayer, glm::vec2 boardPos, float pJumpHeight, float pTime, float pWait);
		virtual ~PlayerBehaviour();

		virtual void update(float pStep) { };
		virtual void activateAbility() = 0;

		void checkKeys();
		void move(float pStep, float pCurTime, float pMoveTime, float pLastMoveTime);
		void finishMove(float pMoveTime, float pLastMoveTime);
		void setDirection();
		void cancelMove();
		void jump(float pHeight);


		void message(sendMsg::Message) { };

		glm::vec2 getBoardPos();
		glm::vec2 getNextPos();
		Id getPlayerId();

	protected:
		void inverseDirection();

		void rotate(float pStep);
		void translate(float pTime, float pMoveTime, float pStep);
		
		Player* _player;

		//settings
		float _dJumpHeight  = 1;
		float _cJumpHeight  = 1;
		float _distance		= 1;

		//vars
		glm::vec2 _boardPos;

		glm::vec3 _axis  = glm::vec3(1,0,0);
		glm::vec3 _trans = glm::vec3(0,0,0);

		float _lastHeight   = 0;

		Dir _cDir = none;
		Dir _dDir = none;

		bool _canceled = false;
};

#endif // ROTATINGBEHAVIOUR_H
