#include "mge/behaviours/MovementBehaviour.hpp"

#include "../game/Level.hpp"
#include "../game/Player.hpp"

#include <SFML/Window/Keyboard.hpp>

#include <algorithm>



MovementBehaviour::MovementBehaviour(Player* pPlayer, glm::vec2 pBoardPos, float pJumpHeight, float const pTime, float pWait) :
	 _player(pPlayer), _boardPos(pBoardPos), _jumpHeight(pJumpHeight), _totalTime(pTime)
{
	_moveTime = _totalTime - _totalTime * std::max(0.f, std::min(pWait, 1.f));
}

void MovementBehaviour::update(float pStep)
{
	checkKeys(); //set desired direction, doesn't update current direction yet

	_curTime += pStep; //total time into the animation

	if (_curTime < _moveTime) //are we moving?
	{
		float cancelTime; //temporary variable for mid air canceling

		if (_canceled && _curTime > (cancelTime = _moveTime / 2.f)) //is the move invalid and are we halfway?
		{
			float step = (_curTime - cancelTime) - (cancelTime - _lastMoveTime);
			
			//inverse the direction and axis
			_axis = -_axis;
			_trans = -_trans;

			//Inverse the desired direction for next move
			Direction tDir = _cDir;
			inverseDirection();

			if (_dDir == tDir)
				_dDir = _cDir;

			roll(step / _moveTime);
			move(_curTime, step);

			_boardPos -= glm::vec2(_trans.x, _trans.z);

			_canceled = false;
		}
		else //do the regular move and roll
		{
			roll(((pStep + _deltaTime) / _moveTime)); //roll
			move(_curTime, pStep + _deltaTime); //move
		}

		_deltaTime = 0; //we don't have time which we have to catch up
		_lastMoveTime = _curTime; //save the last time we moved
	}
	else if (_lastMoveTime != 0) //the move time is over, but did we forgot the last bit?
	{
		roll(1 - _lastMoveTime / _moveTime); //roll the last bit
		move(_moveTime, _moveTime - _lastMoveTime); //move the last bit
		_lastMoveTime = 0; //we are done with the move

		_boardPos += glm::vec2(_trans.x, _trans.z);

		Level::step(_player);
	}

	if (_curTime >= _totalTime) //is the animation done?
	{
		_curTime -= _totalTime; //we don't set it to 0 because we are already into the other animation
		_deltaTime = _curTime; //time we have to catch up next animation
		
		_cDir = _dDir; //set the current direction to the desired one

		if (_cDir != none) //do we have a direction?
			setDirection();
	}
		
}

//if step is 1, we rotate 90 degrees
void MovementBehaviour::roll(float pStep) 
{
	float angle = (glm::pi<float>() / 2.f) * pStep;
	_player->rotate(angle, _axis);
}

//pTime is for the height (phase of sinus wave)
//if Pstep is 1, move to next position
void MovementBehaviour::move(float pTime, float pStep) 
{
	float phase = (pTime / _moveTime);

	float height = std::sin(phase * glm::pi<float>()) * _jumpHeight;
	float difference = height - _lastHeight;
	_lastHeight = height;

	glm::mat4 tMat;

	if (_cDir == none)
		tMat = glm::translate(glm::mat4(), glm::vec3(0, difference, 0));
	else
		tMat = glm::translate(glm::mat4(), (pStep * (_distance / _moveTime) * _trans + glm::vec3(0, difference, 0)));

	_player->setTransform(tMat * _player->getTransform());
}

//sets the axis and translation direction
void MovementBehaviour::setDirection()
{
	glm::mat4 worldMat = _player->getWorldTransform();
	glm::vec4 temp;

	switch (_cDir) //world to local axis
	{
	case up:
		temp = glm::vec4(1, 0, 0, 1) * worldMat;
		_trans = glm::vec3(0, 0, 1);
		break;

	case down:
		temp = glm::vec4(-1, 0, 0, 1) * worldMat;
		_trans = glm::vec3(0, 0, -1);
		break;

	case left:
		temp = glm::vec4(0, 0, -1, 1) * worldMat;
		_trans = glm::vec3(1, 0, 0);
		break;

	case right:
		temp = glm::vec4(0, 0, 1, 1) * worldMat;
		_trans = glm::vec3(-1, 0, 0);
		break;
	}

	_axis = glm::round(glm::normalize(glm::vec3(temp))); //normalize angle for precise movement

	if (Level::outOfBounds(_boardPos + glm::vec2(_trans.x, _trans.z)))
		_canceled = true;
}

void MovementBehaviour::checkKeys()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		_dDir = up;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		_dDir = down;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		_dDir = right;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		_dDir = left;
}

void MovementBehaviour::inverseDirection()
{
	switch (_cDir)
	{
	case up:
		_cDir = down;
		break;

	case down:
		_cDir = up;
		break;

	case left:
		_cDir = right;
		break;

	case right:
		_cDir = left;
		break;
	}
}

Id MovementBehaviour::getPlayerId()
{
	return _player->getId();
}

glm::vec2 MovementBehaviour::getBoardPos()
{
	return _boardPos;
}

MovementBehaviour::~MovementBehaviour()
{
	//dtor
}