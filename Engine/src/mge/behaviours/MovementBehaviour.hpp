#ifndef MOVEMENTBEHAVIOUR_H
#define MOVEMENTBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>


class MovementBehaviour : public AbstractBehaviour
{
	public:
		MovementBehaviour(GameObject* pPlayer);
		virtual ~MovementBehaviour();

		virtual void update(float pStep);
		void message(send::Message) { };
	private:

		void SetDirection();

		enum Direction
		{
			up,
			down,
			left,
			right
		};
		
		GameObject* player;

		//set
		float totalTime = 1;
		float waitPerc = 0.2f;
		float jumpHeight = 0.4f;

		//updated
		glm::vec3 axis = glm::vec3(1,0,0);
		glm::vec3 trans = glm::vec3(1, 0, 0);

		glm::mat4 worldMat;

		bool moving = true;

		float moveTime = totalTime;
		float curTime = moveTime;
		float deltaTime = 0;
		float distance = 1;
		Direction dir = up;
};

#endif // ROTATINGBEHAVIOUR_H
