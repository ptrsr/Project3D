#include "../game/PickUps/VisualPickup.hpp"

#include "mge/materials/LitMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

#include "../game/Player.hpp"
#include "mge/auxiliary/ObjectCache.hpp"

VisualPickup::VisualPickup()
{
	_name = "vusializePickUp";
	GameObject * empty = ObjectCache::find("PowerTablet");
	if (empty != NULL) {
		_objToVisualiseOn = empty;
	}
	_speedTexture = Texture::load(config::MGE_TEXTURE_PATH + "speedTexture.png");
	_splashTexture = Texture::load(config::MGE_TEXTURE_PATH + "splashTexture.png");
	_emptyTexture = Texture::load(config::MGE_TEXTURE_PATH + "emptyTexture.png");

}

void VisualPickup::visualizeSpeed()
{
	/*if (_objToVisualiseOn != NULL && _speedTexture != NULL) {
		_objToVisualiseOn->setMaterial(new TextureMaterial(_speedTexture));
	}*/
}
void VisualPickup::visualizeSplash()
{
	/*if (_objToVisualiseOn != NULL && _splashTexture != NULL) {
		_objToVisualiseOn->setMaterial(new TextureMaterial(_splashTexture));
	}*/
}
void VisualPickup::clear()
{
	/*if (_objToVisualiseOn != NULL && _emptyTexture != NULL) {
		_objToVisualiseOn->setMaterial(new TextureMaterial(_emptyTexture));
	}*/
}