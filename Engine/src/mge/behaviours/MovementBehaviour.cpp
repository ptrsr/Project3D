#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
MovementBehaviour::MovementBehaviour()
{
	_left = false;
	_right = false;
	_forward = true;
	_backward = false;
	
}

MovementBehaviour::~MovementBehaviour()
{
	//dtor
}

void MovementBehaviour::update(float pStep)
{
	float moveSpeed = 1; //default if no keys

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		_forward = true;
		_left = false;
		_right = false;
		_backward = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		_forward = false;
		_left = false;
		_right = false;
		_backward = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		_forward = false;
		_left = false;
		_right = true;
		_backward = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		_forward = false;
		_left = false;
		_right = true;
		_backward = false;
	}
	

	if (_forward) {
		_owner->translate(glm::vec3(0.0f, 0.0f, moveSpeed * pStep));

	}
	else if (_backward) {
		_owner->translate(glm::vec3(0.0f, 0.0f, -moveSpeed * pStep));
	}
	else if (_right) {
		_owner->translate(glm::vec3(moveSpeed * pStep, 0.0f, 0.0f));
	}
	else if (_left) {
		_owner->translate(glm::vec3(-moveSpeed * pStep, 0.0f, 0.0f));
	}
	_owner->rotate(pStep * glm::radians(45.0f), _axis); // rotates 45° per second

	//we can also translate directly, basically we take the z axis from the matrix
	//which is normalized and multiply it by moveSpeed*step, than we add it to the
	//translation component
	//glm::mat4 transform = _owner->getTransform();
	//transform[3] += transform[2] * moveSpeed*pStep;
	//_owner->setTransform(transform);

	//rotate the object in its own local space

	//NOTE:
	//The reason the above happens in the local space of the object and not in the world space
	//is that we use the _owner->translate / rotate shortcuts which in turn call glm::rotate / glm::translate
	//The methods multiply the current transform with the translation/rotation matrix from left to right
	//meaning everything happens in local space.6
	
}
