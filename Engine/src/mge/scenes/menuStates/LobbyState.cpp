#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"
#include "mge/auxiliary/ObjectCache.hpp"
#include "mge/auxiliary/AudioManager.h"

#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials//LitMaterial.hpp"

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"

#include "mge/behaviours/DirectionalLight.hpp"
#include "mge/behaviours/PointLight.hpp"
#include "mge/behaviours/SpotLight.hpp"
#include "../game/Level.hpp"

#include "mge/util/DebugHud.hpp"
#include "mge/util/InputHandler.h"

#include "mge/config.hpp"
#include "mge/scenes/menuStates/LobbyState.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
LobbyState::LobbyState(Player* forPlayer)
{
	_player = forPlayer;
}
//build the game _world
void LobbyState::_initializeScene()
{
	cout << "Lobby initialized" << endl;
	_playerMaterial = (StatueMaterial*)_player->getMaterial();
	Id playerId = _player->getId();
}

GameObject* LobbyState::GetStatue(Id playerId)
{
	if (playerId == 1) {
		return ObjectCache::find("Fire1");
	}
	else if (playerId == 2) {
		return ObjectCache::find("Earth1");
	}
	else if (playerId == 3) {
		return ObjectCache::find("Water1");
	}
	else if (playerId == 4) {
		return ObjectCache::find("Wind1");
	}
	else {
		return NULL;
	}
}

void LobbyState::Update()
{
	if (_delayCounter >= _delay)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			_ready = !_ready;
			UpdateVisual(_player->getId(), _ready);

			_delayCounter = 0;

			Level::get()->CreatePacket(_player->getId(), _ready);
		}
	}
	else
	{
		_delayCounter++;
		_delay = 15;
	}
}

void LobbyState::UpdateVisual(Id playerId, bool value)
{
	cout << "Changing visuals for:" << _player->getId() << endl;
	if (value) {
		//_playerMaterial->setScore(1);
		((StatueMaterial*)(GetStatue(playerId)->getMaterial()))->setScore(1);
	}
	else {
		//_playerMaterial->setScore(0);
		((StatueMaterial*)(GetStatue(playerId)->getMaterial()))->setScore(0);
	}
}

bool LobbyState::isReady() {
	return _ready;
}

void LobbyState::setReady(bool value) {
	_ready = value;
}


int LobbyState::CheckSelection() {
	return 0;
}
GameObject* LobbyState::getPlane() {
	return nullptr;
}

void LobbyState::deleteScene() {
}

LobbyState::~LobbyState()
{
	
	//dtor
}
