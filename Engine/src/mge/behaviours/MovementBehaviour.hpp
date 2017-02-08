#ifndef MOVEMENTBEHAVIOUR_H
#define MOVEMENTBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>

/**
 * Simply rotates the object around its origin
 */
class MovementBehaviour : public AbstractBehaviour
{
	public:
		MovementBehaviour();
		virtual ~MovementBehaviour();

		virtual void update(float pStep);
		void message(send::Message) { };
	private:
		glm::vec3 _axis = glm::vec3(0,1,0);
		bool _left;
		bool _right;
		bool _forward;
		bool _backward;
};

#endif // ROTATINGBEHAVIOUR_H
