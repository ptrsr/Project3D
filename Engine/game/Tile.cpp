#include "Tile.hpp"
#include "mge/core/World.hpp"
#include "mge/config.hpp"
#include "mge/auxiliary/TextureCache.hpp"

#include "Board.hpp"
#include "Level.hpp"

#include "mge/auxiliary/PathFinder.hpp"
#include "mge/auxiliary/BreathFirst.hpp"
#include "Player.hpp"

Tile::Tile(glm::vec3 pPosition, Mesh* pMesh) : GameObject("tile")
{
	this->setLocalPosition(pPosition);
	_boardPos = glm::vec2(pPosition.x, pPosition.z);

	Texture * texture = Texture::load(config::MGE_TEXTURE_PATH + "playfield_tile_sg_Ambient_occlusion.png");
	//_material = new TextureMaterial(texture);
	_material = new LitMaterial();
	this->setMaterial(_material);
	this->setMesh(pMesh);
}

glm::vec2 Tile::getBoardPos()
{
	return _boardPos;
}

vector<Tile*> Tile::getConnections()
{
	vector<Tile*> connections;
	vector<glm::vec2> positions;

	positions.push_back(_boardPos + glm::vec2(0, -1));
	positions.push_back(_boardPos + glm::vec2(0, 1));
	positions.push_back(_boardPos + glm::vec2(-1, 0));
	positions.push_back(_boardPos + glm::vec2(1, 0));


	for each (glm::vec2 pos in positions)
		if (!Level::getBoard()->outOfBounds(pos))
			connections.push_back(Level::getBoard()->getTile(pos));

	return connections;
}

void Tile::setOwner(Id pPlayer)
{
	BreathFirst breathFirst;

	if (_owner != Id::empty)
	{
		Level::getBoard()->changeScore(_owner, -1);

		if (_owner != pPlayer)
		{
			for each (Tile* tile in getConnections())
			{
				if (tile == NULL)
					continue;

				if (tile->getOwner() == _owner)
					Level::getBoard()->checkTile(tile);

				if (tile->getOwner() == pPlayer && tile->_connected == false)
					breathFirst.connect(tile, true);
			}
		}
	}
	_owner = pPlayer;
	Level::getBoard()->changeScore(_owner, 1);

	switch (pPlayer)
	{
	case Id::empty:
		_material->setColor(glm::vec3(1));
		break;

	case Id::p1:
		_material->setColor(glm::vec3(1, 0, 0));
		break;

	case Id::p2:
		_material->setColor(glm::vec3(0, 1, 0));
		break;

	case Id::p3:
		_material->setColor(glm::vec3(0, 0, 1));
		break;

	case Id::p4:
		_material->setColor(glm::vec3(0.87f, 0.72f, 0.53f));
		break;
	}
}

Id Tile::getOwner()
{
	return _owner;
}