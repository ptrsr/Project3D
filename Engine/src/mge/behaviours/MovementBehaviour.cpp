#include "mge/behaviours/MovementBehaviour.hpp"

#include "../game/Level.hpp"
#include "../game/Player.hpp"

#include <SFML/Window/Keyboard.hpp>
#include "../game/Enums.hpp"

#include <algorithm>

MovementBehaviour::MovementBehaviour(Player* pPlayer, glm::vec2 pBoardPos, float pJumpHeight, float const pTime, float pWait, bool controlled) :
	_player(pPlayer), _boardPos(pBoardPos), _cJumpHeight(pJumpHeight), _controlled(controlled)
{ }

void MovementBehaviour::move(float pStep, float pCurTime, float pMoveTime, float pLastMoveTime)
{
	float cancelTime; //temporary variable for mid air canceling

	if (_canceled && pCurTime > (cancelTime = pMoveTime / 2.f)) //is the move invalid and are we halfway?
	{
		float step = (pCurTime - cancelTime) - (cancelTime - pLastMoveTime);

		//inverse the direction and axis
		_axis = -_axis;
		_trans = -_trans;

		//Inverse the desired direction for next move
		Dir tDir = _cDir;
		inverseDirection();

		if (_dDir == tDir)
			_dDir = _cDir;

		rotate(step / pMoveTime);
		translate(pCurTime, pMoveTime, step);

		_boardPos -= glm::vec2(_trans.x, _trans.z);

		_canceled = false;
	}
	else
	{
		rotate((pStep / pMoveTime));
		translate(pCurTime, pMoveTime, pStep);
	}
}

void MovementBehaviour::finishMove(float pMoveTime, float pLastMoveTime)
{
	rotate(1 - pLastMoveTime / pMoveTime);
	translate(pMoveTime, pMoveTime, pMoveTime - pLastMoveTime);

	_boardPos += glm::vec2(_trans.x, _trans.z);
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

	if (_cDir == none)
		tMat = glm::translate(glm::mat4(), glm::vec3(0, difference, 0));
	else
		tMat = glm::translate(glm::mat4(), (pStep * (_distance / pMoveTime) * _trans + glm::vec3(0, difference, 0)));

	_player->setTransform(tMat * _player->getTransform());
}

//sets the axis and translation direction
void MovementBehaviour::setDirection()
{
	_cDir = _dDir;

	if (_cDir == Dir::none)
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
	if (getPlayerId() == p1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			_dDir = Dir::up;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			_dDir = Dir::down;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			_dDir = Dir::right;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			_dDir = Dir::left;
	}
	else if (getPlayerId() == p3)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			_dDir = Dir::up;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			_dDir = Dir::down;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			_dDir = Dir::right;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			_dDir = Dir::left;
	}
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
}

void MovementBehaviour::jump(float pHeight)
{
	_cJumpHeight = pHeight;
}

Id MovementBehaviour::getPlayerId()
{
	return _player->getId();
}

bool MovementBehaviour::IsControlled()
{
	return _controlled;
}

glm::vec2 MovementBehaviour::getBoardPos()
{
	return _boardPos;
}

glm::vec2 MovementBehaviour::getNextPos()
{
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