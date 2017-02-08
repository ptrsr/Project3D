#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

MovementBehaviour::MovementBehaviour(GameObject* pPlayer) : player(pPlayer)
{
	moveTime = totalTime - totalTime * waitPerc;
}

MovementBehaviour::~MovementBehaviour()
{
	//dtor
}

void MovementBehaviour::update(float pStep)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		dir = up;
		trans = glm::vec3(0, 0, 1);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		dir = down;
		trans = glm::vec3(0, 0, -1);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		dir = right;
		trans = glm::vec3(1, 0, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		dir = left;
		trans = glm::vec3(-1, 0, 0);
	}

	curTime += pStep;

	glm::mat4 mat = glm::mat4();
	glm::mat4 mat2 = glm::mat4();

	if (curTime < moveTime)
	{
		float angle = (glm::pi<float>() / 2.f) * ((pStep + deltaTime) / moveTime);

		mat2 = glm::translate(mat2, trans * ((pStep + deltaTime) / moveTime));
		mat = glm::rotate(mat, angle, axis);

		player->setTransform(player->getTransform() * mat * mat2);

		deltaTime = 0;
	}

	if (curTime >= totalTime)
	{
		curTime -= totalTime;
		deltaTime = curTime;
		
		SetDirection();
	}
		
}

void MovementBehaviour::SetDirection()
{
	worldMat = player->getWorldTransform();
	glm::vec4 temp;

	switch (dir)
	{
	case up:
		temp = glm::vec4(1, 0, 0, 1) * worldMat;
		break;

	case down:
		temp = glm::vec4(-1, 0, 0, 1) * worldMat;
		break;

	case left:
		temp = glm::vec4(0, 0, -1, 1) * worldMat;
		break;

	case right:
		temp = glm::vec4(0, 0, 1, 1) * worldMat;
		break;
	}

	axis = glm::round(glm::normalize(glm::vec3(temp.x, temp.y, temp.z)));
}