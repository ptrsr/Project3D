#include "PickUp.hpp"
#include "mge/core/World.hpp"
#include "SFML/Window/Keyboard.hpp"

#include "../game/Level.hpp"

#include <algorithm>

PickUp::PickUp(std::string pName) : GameObject(pName)
{
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
}

void PickUp::step()
{
	if (_countDown == -1)
		return;

	_countDown--;

	if (_countDown == 0)
		spawn();
}

void PickUp::hover(float pStep)
{
	
}

PickUp::~PickUp()
{
	std::vector<PickUp*>& pickUps = Level::getPickUps();
	pickUps.erase(std::remove(pickUps.begin(), pickUps.end(), this), pickUps.end());
}