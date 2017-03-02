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

		virtual inline void update(float pStep);

		void checkKeys();
		void move(float pStep);
		void finishMove(float pMoveTime, float pLastMoveTime);
		void setDirection();
		void cancelMove();
		void jump(float pHeight);
		void fireAbility(bool toggle);

		void message(sendMsg::Message) { };

		glm::vec2 getBoardPos();
		glm::vec2 getNextPos();
		void enableAbility();

	private:
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

		float _curTime		= 0;
		float _deltaTime	= 0;
		float _lastMoveTime = 0;
		float _totalTime	= 0;
		float _moveMulti	= 1;

		float _moveTime		= 0;

		float _lastHeight   = 0;

		Dir _cDir = emtpy;
		Dir _dDir = emtpy;

		bool _canceled = false;
		bool _activate = false;
		bool _available = true;
};

#endif // ROTATINGBEHAVIOUR_H
