#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

#include <algorithm>

MovementBehaviour::MovementBehaviour(GameObject* pPlayer, float pJumpHeight, float pTime, float pWait) : 
	player(pPlayer), jumpHeight(pJumpHeight), totalTime(pTime)
{
	waitPerc = std::max(0.f, std::min(pWait, 1.f));
	moveTime -= totalTime * waitPerc;
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
		roll(((pStep + deltaTime) / moveTime));
		move(curTime, pStep);

		deltaTime = 0;
		missed = 1 - (curTime / moveTime);
	}
	else if (missed != 0)
	{
		roll(missed);
		move(moveTime, pStep);
		missed = 0;
	}

	if (curTime >= totalTime)
	{
		curTime -= totalTime;
		deltaTime = curTime;
		
		setDirection();
	}
		
}

void MovementBehaviour::roll(float pStep)
{
	float angle = (glm::pi<float>() / 2.f) * pStep;
	player->rotate(angle, axis);
}

void MovementBehaviour::move(float pTime, float pStep)
{
	float phase = (pTime / moveTime);

	float height = std::sin(phase * glm::pi<float>()) * jumpHeight;
	float difference = height - lastHeight;
	lastHeight = height;

	glm::mat4 tMat = glm::translate(glm::mat4(), (pStep * (distance / moveTime) * trans + glm::vec3(0, difference, 0)));
	//glm::mat4 tMat = glm::translate(glm::mat4(), glm::vec3(0, difference, 0) );
	player->setTransform(tMat * player->getTransform());
}

void MovementBehaviour::setDirection()
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