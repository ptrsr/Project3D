#include "PickUp.hpp"
#include "mge/core/World.hpp"
#include "SFML/Window/Keyboard.hpp"

#include "../game/Level.hpp"

#include <algorithm>

PickUp::PickUp(std::string pName, float moveTime) : GameObject(pName)
{
	_moveTime = moveTime;

	srand(time(NULL));

	World::add(this);
}

void PickUp::spawn()
{
	std::cout << "spawned" << std::endl;

	std::vector<glm::vec2> positions;

	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			glm::vec2 pos = glm::vec2(i, j);
			bool available = true;

			for each (Player* player in Level::getPlayers())
			{
				glm::vec2 dif = player->getBoardPos() - pos;

				if (std::abs(dif.x) <= 1 && std::abs(dif.y) <= 1 && ((!dif.x && !dif.y) || (dif.x && !dif.y) || (!dif.x && dif.y)))
				{
					available = false;
					break;
				}
			}

			for each (PickUp* pickUp in Level::getPickUps())
			{
				if (pickUp->getBoardPos() == pos)
				{
					available = false;
					break;
				}
			}

			if (available)
				positions.push_back(pos);
		}
	}

	_boardPos = positions[std::rand() % positions.size()];
	setLocalPosition(glm::vec3(_boardPos.x, _spawnHeight, _boardPos.y));
}

glm::vec2 PickUp::getBoardPos()
{
	return _boardPos;
}

void PickUp::reset()
{
	_boardPos = glm::vec2(-1);
	setLocalPosition(glm::vec3(0, -10, 0));
	_countDown = (rand() % (_maxDelay - _minDelay)) + _minDelay;
	_floatTimer = 0;
}

void PickUp::step()
{
	_countDown--;

	if (_countDown < 0)
		return;

	if (_countDown == 0)
	{
		spawn();
		std::cout << "spawn" << std::endl;
	}
}

void PickUp::hover(float pStep)
{
	if (_countDown <= 0)
	{
		_floatTimer += pStep;

		rotate((glm::sin(_floatTimer) + 2) / 30.f, glm::normalize(glm::vec3(sin(_floatTimer), cos(_floatTimer), -sin(_floatTimer))));

		float height = glm::sin(_floatTimer) * _hoverDif + _hoverHeight;

		if (_floatTimer <= _moveTime)
		{
			float multiplier = 1 - _floatTimer / _moveTime;
			height += (multiplier * multiplier) * (_spawnHeight - height);
		}
		
		setLocalPosition(glm::vec3(_boardPos.x, height, _boardPos.y));
	}
}

PickUp::~PickUp()
{
	std::vector<PickUp*>& pickUps = Level::getPickUps();
	pickUps.erase(std::remove(pickUps.begin(), pickUps.end(), this), pickUps.end());
}