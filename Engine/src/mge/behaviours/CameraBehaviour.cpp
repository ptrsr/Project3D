#include "mge/behaviours/CameraBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

#include <algorithm>


CameraBehaviour::CameraBehaviour(GameObject* pTarget)
{
	_target = pTarget;
}

CameraBehaviour::~CameraBehaviour()
{
	//dtor
}

void CameraBehaviour::changeTarget(GameObject* newTarget) {
	_target = newTarget;
}

void CameraBehaviour::update(float pStep)
{

	glm::mat4 currentPos = _target->getTransform();
	glm::mat4 newPos = _owner->getTransform();
	//glm::vec3 forward = glm::normalize(_owner->getLocalPosition() - _target->getLocalPosition());
	//glm::vec3 right = glm::cross(glm::vec3(0, 1, 0), forward);
	//glm::vec3 up = glm::cross(forward, right);

	//newPos = glm::mat4(glm::vec4(right, 0), glm::vec4(up, 0), glm::vec4(forward, 0), glm::vec4(_owner->getLocalPosition(), 1));
	newPos = newPos*(1 - pStep) + currentPos*pStep;
	cout << newPos << endl;

	_owner->setTransform(newPos);


}