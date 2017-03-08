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
	if (playerId == 1) {
		_playerStatue = ObjectCache::find("Fire1");
	}
	else if (playerId == 2) {
		_playerStatue = ObjectCache::find("Earth1");
	}
	else if (playerId == 3) {
		_playerStatue = ObjectCache::find("Water1");
	}
	else if (playerId == 4) {
		_playerStatue = ObjectCache::find("Wind1");
	}
	else {
		_playerStatue = NULL;
	}
	
}

void LobbyState::Update() {

	cout << "Lobby updated" << endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (_ready) _ready = false;
		else { _ready = true; }
		_updateVisual();
	}

	if (_isKeyPress) {
		if (_delayCounter >= _delay) {
			_delayCounter = 0;
			_isKeyPress = false;
		}
		else {
			_delayCounter++;
			_delay = 15;
		}
	}
}

void LobbyState::_updateVisual() {
	cout << "Changing visuals for:" << _player->getId() << endl;
	if (_ready) {
		//_playerMaterial->setScore(1);
		((StatueMaterial*)(_playerStatue->getMaterial()))->setScore(1);
	}
	else {
		//_playerMaterial->setScore(0);
		((StatueMaterial*)(_playerStatue->getMaterial()))->setScore(0);
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
