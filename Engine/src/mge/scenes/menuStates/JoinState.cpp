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
#include "mge/scenes/menuStates/JoinState.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
JoinState::JoinState()
{
}
//Sets the scene for the credits
void JoinState::_initializeScene()
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");


	GameObject * plane = ObjectCache::find("creditsPlane");
	if (plane != NULL) {
		_plane = plane;
	}
	GameObject * backText = ObjectCache::find("back_text1");
	if (backText != NULL) {
		_back = backText;
	}
	GameObject * enterIp = ObjectCache::find("enterip_text");
	if (enterIp != NULL) {
		_enterIp = enterIp;
	}

	_text = new Text(TextType::IP);
	_text->_initializeScene();

}
//Update called outside of the class
void JoinState::Update() {
	_updateColor();
}

//Clears and updates the color of the object you are currently on(applies some delay for keyDown like behaviour)
void JoinState::_updateColor() {
	
	if (_counter == 0) {
		_text->Update();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isKeyPress) {
		_isKeyPress = true;
		if (_counter == 0) {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_enterIp->getMaterial()->setColor(glm::vec3(1, 0, 0)); 
			_back->getMaterial()->setColor(glm::vec3(1, 1, 1));
			_counter = 1;
		}
		else {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_counter = 0;
			_enterIp->getMaterial()->setColor(glm::vec3(1, 1, 1));
			_back->getMaterial()->setColor(glm::vec3(1, 0, 0));
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isKeyPress) {
		_isKeyPress = true;
		if (_counter == 0) {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_enterIp->getMaterial()->setColor(glm::vec3(1, 0, 0));
			_back->getMaterial()->setColor(glm::vec3(1, 1, 1));
			_counter = 1;
		}
		else {
			AudioManager::get()->PlaySound(SFX::switchButton1);
			_counter = 0;
			_enterIp->getMaterial()->setColor(glm::vec3(1, 1, 1));
			_back->getMaterial()->setColor(glm::vec3(1, 0, 0));
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
//check if you selected
int JoinState::CheckSelection() {
	if (_counter == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !_isKeyPress) {
			_inAnotherState = true;
			_isKeyPress = true;
			_back->getMaterial()->setColor(glm::vec3(1, 1, 1));
			AudioManager::get()->PlaySound(SFX::backButton1);
			return -1;
		}
	}
	else return 2;
}

//Gets the object to use as the LookAt object of the camera
GameObject* JoinState::getPlane() {
	return _plane;
}



//Clear objectsColor
void JoinState::_clearObjectColor() {
}

void JoinState::deleteScene() {
}

JoinState::~JoinState()
{

}
