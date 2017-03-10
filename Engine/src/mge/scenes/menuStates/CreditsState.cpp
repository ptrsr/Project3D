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

#include "mge/materials/TextureMaterial.hpp"
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
#include "mge/scenes/menuStates/CreditsState.hpp"
#include "mge/materials/ChangeColorMaterial.hpp"

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
CreditsState::CreditsState()
{
}
//build the game _world
void CreditsState::_initializeScene()
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	GameObject * plane = ObjectCache::find("joinPlane");
	if (plane != NULL) {
		_plane = plane;
	}

	GameObject * back = ObjectCache::find("back_text");
	if (back != NULL)
	{
		_selectableObj = back;
		back->setMaterial(new ChangeColorMaterial(Texture::load(config::MGE_TEXTURE_PATH + "back_diffuse.png"), Texture::load(config::MGE_TEXTURE_PATH + "back.png"), glm::vec3(1)));
	}

	
}

void CreditsState::Update() {
	_inAnotherState = false;
	_updateColor();

	if (_inAnotherState) return;
	if (_isKeyPress) {
		_delayCounter++;
		if (_delayCounter == _delay) {
			_delayCounter = 0;
			_isKeyPress = false;
		}
	}
}

void CreditsState::_updateColor() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isKeyPress) {
		_isKeyPress = true;
		if (_counter == 0) {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_selectableObj->getMaterial()->setColor(glm::vec3(1, 0, 0));
			_counter = 1;
		}
		else {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_counter = 0;
			_selectableObj->getMaterial()->setColor(glm::vec3(1, 1, 1));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isKeyPress) {
		_isKeyPress = true;
		if (_counter == 0) {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_selectableObj->getMaterial()->setColor(glm::vec3(1, 0, 0));
			_counter = 1;
		}
		else {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_counter = 0;
			_selectableObj->getMaterial()->setColor(glm::vec3(1, 1, 1));
		}
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

int CreditsState::CheckSelection() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !_isKeyPress) {
		cout << "Going back to start" << endl;
		_isKeyPress = true;
		_inAnotherState = true;

		AudioManager::get()->PlaySound(SFX::backButton1);
		return -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_isKeyPress) {
		cout << "Going back to start" << endl;
		_isKeyPress = true;
		_inAnotherState = true;
		AudioManager::get()->PlaySound(SFX::backButton1);
		return -1;
	}
	
	else return 1;
}
GameObject* CreditsState::getPlane() {
	return _plane;
}

void CreditsState::deleteScene() {
	World::remove(_plane);
	World::remove(_selectableObj);
	World::remove(_writingStone);
	delete _plane;
	delete _selectableObj;
	delete _writingStone;
}

CreditsState::~CreditsState()
{
	
	//dtor
}
