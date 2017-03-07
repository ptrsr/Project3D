#include "Tile.hpp"
#include "mge/core/World.hpp"
#include "mge/config.hpp"
#include "mge/auxiliary/TextureCache.hpp"

#include "Board.hpp"
#include "Level.hpp"

#include "mge/auxiliary/PathFinder.hpp"
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

	connections.push_back(Level::getBoard()->getTile(_boardPos + glm::vec2(0, -1))); //up
	connections.push_back(Level::getBoard()->getTile(_boardPos + glm::vec2(0, 1)));  //down
	connections.push_back(Level::getBoard()->getTile(_boardPos + glm::vec2(-1, 0))); //left
	connections.push_back(Level::getBoard()->getTile(_boardPos + glm::vec2(1, 0)));  //right

	for (int i = 0; i < connections.size(); i++)
		if (!connections[i])
			connections.erase(connections.begin() + i);

	return connections;
}

void Tile::setOwner(Id pPlayer)
{
	if (_owner != Id::none && _owner != pPlayer)
	{
		for (int j = -1; j <= 1; j++)
			for (int i = -1; i <= 1; i++)
			{
				Tile* tile = Level::getBoard()->getTile(_boardPos + glm::vec2(i, j));

				if (tile && tile->getOwner() == _owner)
					Level::getBoard()->checkTile(tile);
			}

		std::cout << PathFinder::canReach(this, Level::getBoard()->getTile(Level::getPlayer(_owner)->getBoardPos()));
	}


	_owner = pPlayer;

	switch (pPlayer)
	{
	case emtpy:
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