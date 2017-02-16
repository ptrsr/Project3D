#ifndef MOVEMENTBEHAVIOUR_H
#define MOVEMENTBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"

class Player;

class MovementBehaviour : public AbstractBehaviour
{

	public:
		MovementBehaviour(Player* pPlayer, glm::vec2 boardPos, float pJumpHeight, float pTime, float pWait);
		virtual ~MovementBehaviour();

		virtual void update(float pStep);
		void message(sendMsg::Message) { };

		glm::vec2 getBoardPos();
		Id getPlayerId();

	private:
		enum Direction
		{
			none,
			up,
			down,
			left,
			right
		};

		void checkKeys();
		void setDirection();
		void inverseDirection();

		void roll(float pStep);
		void move(float pPhase, float pTime);
		
		Player* _player;

		//settings
		float _totalTime;
		float _moveTime;

		float _jumpHeight	= 1;
		float _distance		= 1;

		//vars
		glm::vec2 _boardPos;

		glm::vec3 _axis  = glm::vec3(1,0,0);
		glm::vec3 _trans = glm::vec3(0,0,0);

		float _curTime      = 0;
		float _deltaTime    = 0;
		float _lastMoveTime = 0;
		float _lastHeight   = 0;

		Direction _cDir = none;
		Direction _dDir = none;

		bool _canceled = false;
};

#endif // ROTATINGBEHAVIOUR_H
