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
		dir = up;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		dir = down;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dir = right;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dir = left;

	curTime += pStep;

	if (curTime < moveTime)
	{
		float angle = (glm::pi<float>() / 2.f) * ((pStep + deltaTime) / moveTime);
		player->rotate(angle, axis);

		glm::vec3 height = glm::vec3(0, std::sin((curTime * (totalTime / moveTime)) * glm::pi<float>() * 2), 0) / 5.f;

		glm::mat4 tMat = glm::translate(glm::mat4(), (trans * ((pStep + deltaTime) / moveTime) + height));
		player->setTransform(tMat * player->getTransform());

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
		trans = glm::vec3(0, 0, 1);
		break;

	case down:
		temp = glm::vec4(-1, 0, 0, 1) * worldMat;
		trans = glm::vec3(0, 0, -1);
		break;

	case left:
		temp = glm::vec4(0, 0, -1, 1) * worldMat;
		trans = glm::vec3(1, 0, 0);
		break;

	case right:
		temp = glm::vec4(0, 0, 1, 1) * worldMat;
		trans = glm::vec3(-1, 0, 0);
		break;
	}

	axis = glm::round(glm::normalize(glm::vec3(temp.x, temp.y, temp.z)));
}