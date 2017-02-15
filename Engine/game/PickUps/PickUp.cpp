#include "PickUp.hpp"
#include "mge/core/World.hpp"
#include "SFML/Window/Keyboard.hpp"

#include <algorithm>

std::vector<PickUp*> PickUp::_pickUps;

PickUp::PickUp(std::string pName, std::vector<MovementBehaviour*> pPlayers) : GameObject(pName)
{
	srand(time(NULL));

	_players = pPlayers;
	
	World::add(this);
	_pickUps.push_back(this);

	spawn();
}

std::vector<PickUp*> PickUp::getPickUps()
{
	return _pickUps;
}

void PickUp::spawn()
{
	std::vector<glm::vec2> positions;

	for (int j = 0; j < 9; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			glm::vec2 pos = glm::vec2(i, j);
			bool available = true;

			for each (MovementBehaviour* player in _players)
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
	setLocalPosition(glm::vec3(_boardPos.x, 1, _boardPos.y));
}

glm::vec2 PickUp::getBoardPos()
{
	return _boardPos;
}

PickUp::~PickUp()
{
	_pickUps.erase(std::remove(_pickUps.begin(), _pickUps.end(), this), _pickUps.end());
}