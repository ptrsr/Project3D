#include "mge/behaviours/MovementBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>

#include <algorithm>


MovementBehaviour::MovementBehaviour(GameObject* pPlayer, Tile* pBoardArray[9][9], float pJumpHeight, float pTime, float pWait) :
	 player(pPlayer), jumpHeight(pJumpHeight), totalTime(pTime)
{
	//boardArray = pBoardArray;
	waitPerc = std::max(0.f, std::min(pWait, 1.f));
	moveTime -= totalTime * waitPerc;
}

MovementBehaviour::~MovementBehaviour()
{
	//dtor
}

void MovementBehaviour::update(float pStep)
{
	checkKeys(); //set desired direction, doesn't update current direction yet

	curTime += pStep; //total time into the animation

	if (curTime < moveTime) //are we moving?
	{
		roll(((pStep + deltaTime) / moveTime)); //roll
		move(curTime, pStep + deltaTime); //move

		deltaTime = 0; //we don't have time which we have to catch up
		lastMoveTime = curTime; //save the last time we moved
	}
	else if (lastMoveTime != 0) //the move time is over, but did we forgot the last bit?
	{
		roll(1 - lastMoveTime / moveTime); //roll the last bit
		move(moveTime, moveTime - lastMoveTime); //move the last bit
		lastMoveTime = 0; //we are done with the move
	
		
	}

	if (curTime >= totalTime) //is the animation done?
	{
		curTime -= totalTime; //we don't set it to 0 because we are already into the other animation
		deltaTime = curTime; //time we have to catch up next animation
		
		cDir = dDir; //set the current direction to the desired one

		if (cDir != none) //do we have a direction?
			setDirection();
	}
		
}

//if step is 1, we rotate 90 degrees
void MovementBehaviour::roll(float pStep) 
{
	float angle = (glm::pi<float>() / 2.f) * pStep;
	player->rotate(angle, axis);
}

//pTime is for the height (phase of sinus wave)
//if Pstep is 1, move to next position
void MovementBehaviour::move(float pTime, float pStep) 
{
	float phase = (pTime / moveTime);

	float height = std::sin(phase * glm::pi<float>()) * jumpHeight;
	float difference = height - lastHeight;
	lastHeight = height;

	glm::mat4 tMat;

	if (cDir == none)
		tMat = glm::translate(glm::mat4(), glm::vec3(0, difference, 0));
	else
		tMat = glm::translate(glm::mat4(), (pStep * (distance / moveTime) * trans + glm::vec3(0, difference, 0)));

	player->setTransform(tMat * player->getTransform());
}

//sets the axis and translation direction
void MovementBehaviour::setDirection()
{
	worldMat = player->getWorldTransform();
	glm::vec4 temp;

	switch (cDir) //world to local axis
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

	axis = glm::round(glm::normalize(glm::vec3(temp))); //normalize angle for precise movement
}

void MovementBehaviour::checkKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		dDir = up;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		dDir = down;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dDir = right;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dDir = left;
}