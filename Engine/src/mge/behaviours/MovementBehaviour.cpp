#include "mge/behaviours/MovementBehaviour.hpp"

#include "../game/Level.hpp"
#include "../game/Player.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "../game/Enums.hpp"

#include <algorithm>

MovementBehaviour::MovementBehaviour(Player* pPlayer, glm::vec2 pBoardPos, float pJumpHeight, float const pTime, float pWait) :
	_player(pPlayer), _boardPos(pBoardPos), _cJumpHeight(pJumpHeight), _totalTime(pTime), _moveTime(glm::clamp(pTime * ( 1 - pWait), 0.f, 1.f))
{ }

void MovementBehaviour::update(float pStep)
{
	_curTime += pStep;

	checkKeys();

	if (_curTime < _moveTime)
	{
		move(pStep + _deltaTime);

		_deltaTime = 0;
		_lastMoveTime = _curTime;
	}
	//if move ended
	else if (_lastMoveTime != 0)
	{
		//finish player animation
		finishMove(_moveTime, _lastMoveTime);

		//set tiles to new owner
		Level::getBoard()->setOwner(getBoardPos(), _player->getId());

		//apply pickups
		Level::applyPickUp(_player);

		//apply areas
		Level::checkArea();

		_lastMoveTime = 0;
	}

	if (_curTime >= _totalTime)
	{
		//set next move direction to desired direction
		setDirection();

		//reset time for next step
		_curTime -= _totalTime;
		_deltaTime = _curTime;

		if (_activate)
		{
			_activate = false;
			Level::applyAbility(_player);
		}
	}
}

void MovementBehaviour::move(float pStep)
{
	float cancelTime; //temporary variable for mid air canceling

	if (_canceled && _curTime > (cancelTime = _moveTime / 2.f)) //is the move invalid and are we halfway?
	{
		float step = (_curTime - cancelTime) - (cancelTime - _lastMoveTime);
			
		//inverse the direction and axis
		_axis = -_axis;
		_trans = -_trans;

		//Inverse the desired direction for next move
		Dir tDir = _cDir;
		inverseDirection();

		if (_dDir == tDir)
			_dDir = _cDir;

		rotate(step / _moveTime);
		translate(_curTime, _moveTime, step);

		_canceled = false;
		_wasCanceled = true;
	}
	else
	{
		rotate((pStep / _moveTime));
		translate(_curTime, _moveTime, pStep);
	}
}

void MovementBehaviour::finishMove(float pMoveTime, float pLastMoveTime)
{
	rotate(1 - pLastMoveTime / pMoveTime);
	translate(pMoveTime, pMoveTime, pMoveTime - pLastMoveTime);

	if (!_wasCanceled)
		_boardPos += glm::vec2(_trans.x, _trans.z);

	_wasCanceled = false;

	_cJumpHeight = _dJumpHeight;
}

//if step is 1, we rotate 90 degrees
void MovementBehaviour::rotate(float pStep) 
{
	float angle = (glm::pi<float>() / 2.f) * pStep;
	_player->rotate(angle, _axis);
}

//pTime is for the height (phase of sinus wave)
//if Pstep is 1, move to next position
void MovementBehaviour::translate(float pTime, float pMoveTime, float pStep) 
{
	float height = std::sin((pTime / pMoveTime) * glm::pi<float>()) * _cJumpHeight;
	float difference = height - _lastHeight;
	_lastHeight = height;

	glm::mat4 tMat;

	if (_cDir == emtpy)
		tMat = glm::translate(glm::mat4(), glm::vec3(0, difference, 0));
	else
		tMat = glm::translate(glm::mat4(), (pStep * (_distance / pMoveTime) * _trans + glm::vec3(0, difference, 0)));

	_player->setTransform(tMat * _player->getTransform());
}

//sets the axis and translation direction
void MovementBehaviour::setDirection()
{
	_cDir = _dDir;

	if (_cDir == Dir::emtpy)
		return;

	glm::mat4 worldMat = _player->getWorldTransform();
	glm::vec4 temp;

	switch (_cDir) //world to local axis
	{
	case Dir::up:
		temp = glm::vec4(1, 0, 0, 1) * worldMat;
		_trans = glm::vec3(0, 0, 1);
		break;

	case Dir::down:
		temp = glm::vec4(-1, 0, 0, 1) * worldMat;
		_trans = glm::vec3(0, 0, -1);
		break;

	case Dir::left:
		temp = glm::vec4(0, 0, -1, 1) * worldMat;
		_trans = glm::vec3(1, 0, 0);
		break;

	case Dir::right:
		temp = glm::vec4(0, 0, 1, 1) * worldMat;
		_trans = glm::vec3(-1, 0, 0);
		break;
	}

	_axis = glm::round(glm::normalize(glm::vec3(temp))); //normalize angle for precise movement

	if (!Level::checkAvailable(_player))
		_canceled = true;
}

void MovementBehaviour::checkKeys()
{
	if (_player->getId() == p1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			_dDir = Dir::up;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			_dDir = Dir::down;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			_dDir = Dir::right;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			_dDir = Dir::left;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _available)
		{
			_activate = true;
			//_available = false;

		}
	}
	else if (_player->getId() == p3)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_dDir = Dir::up;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_dDir = Dir::down;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_dDir = Dir::right;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_dDir = Dir::left;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && _available)
		{
			_activate = true;
			//_available = false;
		}
	}
}

void MovementBehaviour::enableAbility()
{
	_available = true;
}

void MovementBehaviour::inverseDirection()
{
	switch (_cDir)
	{
	case Dir::up:
		_cDir = Dir::down;
		break;

	case Dir::down:
		_cDir = Dir::up;
		break;

	case Dir::left:
		_cDir = Dir::right;
		break;

	case Dir::right:
		_cDir = Dir::left;
		break;
	}
}

void MovementBehaviour::cancelMove()
{
	_canceled = true;
	_boardPos -= glm::vec2(_trans.x, _trans.z);
}

void MovementBehaviour::jump(float pHeight)
{
	_cJumpHeight = pHeight;
}



glm::vec2 MovementBehaviour::getBoardPos()
{
	return _boardPos;
}

void MovementBehaviour::fireAbility(bool toggle)
{
	if (toggle)
		_totalTime = _moveTime;
	else
		_totalTime = _moveTime * 2;

	std::cout << _moveTime * 2;
}

void MovementBehaviour::earthAbility(bool toggle)
{
	_activate = false;
	_available = false;
}

glm::vec2 MovementBehaviour::getNextPos()
{
	if (_canceled)
		return _boardPos;

	glm::vec2 dPos;


	switch (_dDir)
	{
	case Dir::up:
		dPos = glm::vec2(0, 1);
		break;

	case Dir::down:
		dPos = glm::vec2(0, -1);
		break;
	
	case Dir::left:
		dPos = glm::vec2(1, 0);
		break;

	case Dir::right:
		dPos = glm::vec2(-1, 0);
		break;
	}

	return dPos + _boardPos;
}

MovementBehaviour::~MovementBehaviour()
{
	//dtor
}