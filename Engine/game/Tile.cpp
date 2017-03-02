#include "Tile.hpp"
#include "mge/core/World.hpp"
#include "mge/config.hpp"
#include "mge/auxiliary/TextureCache.hpp"

Tile::Tile(glm::vec3 pPosition, Mesh* pMesh) : GameObject("tile")
{
	this->setLocalPosition(pPosition);

	Texture * texture = Texture::load(config::MGE_TEXTURE_PATH + "playfield_tile_sg_Ambient_occlusion.png");
	//_material = new TextureMaterial(texture);
	_material = new LitMaterial();
	this->setMaterial(_material);
	this->setMesh(pMesh);
}

void Tile::setOwner(Id pPlayer)
{
	_owner = pPlayer;

	switch (pPlayer)
	{
	case emtpy:
		_material->setColor(glm::vec3(1));
		break;

	case fire:
		_material->setColor(glm::vec3(1, 0, 0));
		break;

	case earth:
		_material->setColor(glm::vec3(0, 1, 0));
		break;

	case water:
		_material->setColor(glm::vec3(0, 0, 1));
		break;

	case wind:
		_material->setColor(glm::vec3(0.87f, 0.72f, 0.53f));
		break;
	}
}

Id Tile::getOwner()
{
	return _owner;
}