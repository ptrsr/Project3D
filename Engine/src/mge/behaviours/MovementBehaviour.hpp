#ifndef MOVEMENTBEHAVIOUR_H
#define MOVEMENTBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"
#include "../game/Direction.hpp"

class MovementBehaviour : public AbstractBehaviour
{
	class Player;

	public:
		MovementBehaviour(GameObject* pPlayer, Id playerId, glm::vec2 boardPos, float pJumpHeight, float pTime, float pWait, bool isPlayer);
		virtual ~MovementBehaviour();

		virtual void update(float pStep);
		void message(sendMsg::Message) { };

		glm::vec2 getBoardPos();
		Id getPlayerId();
		
		void setDesiredDirection(Direction dir);
	private:
		void checkKeys();
		void inverseDirection();
		void setDirection();

		void roll(float pStep);
		void move(float pPhase, float pTime);
		
		GameObject* _player;
		Id		    _id;
		bool		_isPlayer;

		//settings
		float _totalTime  = 1;
		float _moveTime;

		float _jumpHeight = 0.4f;
		float _distance	  = 1;

		//vars
		glm::vec2 _boardPos;

		glm::vec3 _axis  = glm::vec3(1,0,0);
		glm::vec3 _trans = glm::vec3(0,0,0);

		float _curTime      = 0;
		float _deltaTime    = 0;
		float _lastMoveTime = 0;
		float _lastHeight   = 0;
		
		Direction _cDir = Direction::idle;
		Direction _dDir = Direction::idle;

		bool _canceled = false;
};

#endif // ROTATINGBEHAVIOUR_H
