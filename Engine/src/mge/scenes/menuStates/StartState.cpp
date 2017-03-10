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
#include "mge/scenes/menuStates/StartState.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
StartState::StartState()
{
}
//build the game _world
void StartState::_initializeScene()
{

	GameObject * plane = ObjectCache::find("mainPlane");
	if (plane != NULL) {
		_plane = plane;
		
	}
	GameObject * create = ObjectCache::find("create_text");
	if (create != NULL)
	{
		_selectableObjs[0] = create;
		create->setMaterial(new ChangeColorMaterial(Texture::load(config::MGE_TEXTURE_PATH + "create_diffuse.png"), Texture::load(config::MGE_TEXTURE_PATH + "create.png"), glm::vec3(1)));
	}

	GameObject * join = ObjectCache::find("join_text");
	if (join != NULL) {
		_selectableObjs[1] = join;
		join->setMaterial(new ChangeColorMaterial(Texture::load(config::MGE_TEXTURE_PATH + "join_diffuse.png"), Texture::load(config::MGE_TEXTURE_PATH + "join.png"), glm::vec3(0)));
	}
	GameObject * credits = ObjectCache::find("credits_text");
	if (credits != NULL)
	{
		_selectableObjs[2] = credits;
		credits->setMaterial(new ChangeColorMaterial(Texture::load(config::MGE_TEXTURE_PATH + "credits_diffuse.png"), Texture::load(config::MGE_TEXTURE_PATH + "credits.png"), glm::vec3(0)));
	}
	GameObject * quit = ObjectCache::find("quit");
	if (quit != NULL) {
		_selectableObjs[3] = quit;
		credits->setMaterial(new ChangeColorMaterial(Texture::load(config::MGE_TEXTURE_PATH + "quit_diffuse.png"), Texture::load(config::MGE_TEXTURE_PATH + "quit.png"), glm::vec3(0)));
	}

	
}

void StartState::Update() {
	_inAnotherState = false;
	_updateColor();
}

GameObject* StartState::getPlane() {
	return _plane;
}

int StartState::CheckSelection() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !_isKeyPress) {
		_inAnotherState = true;
		_isKeyPress = true;
		if (_selectableObjs[_counter]->getName() == "create_text") {
			return 3;
		}
		if (_selectableObjs[_counter]->getName() == "join_text") {
			return 2;
		}
		else if (_selectableObjs[_counter]->getName() == "credits_text") {

			return 1;
		}

		else if (_selectableObjs[_counter]->getName() == "quit") {

			return 0;
		}
	}
	else return -1;
}


void StartState::_updateColor() {
	if (_inAnotherState) return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isKeyPress) {
		_isKeyPress = true;
		if (_counter == 0) _counter = 2;
		if (_counter == 1) _counter = 3;

		AudioManager::get()->PlaySoundW(SFX::switchButton1);
		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1));
		//gObj->scale(glm::vec3(1, 1.0f, 2.0f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isKeyPress) {
		_isKeyPress = true;

		if (_counter == 2) _counter = 0;
		if (_counter == 3) _counter = 1;
		AudioManager::get()->PlaySoundW(SFX::switchButton1);
		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1));
		//gObj->scale(glm::vec3(1, 1.0f, 2.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !_isKeyPress) {
		_isKeyPress = true;

		if (_counter == 1) _counter = 0;
		if (_counter == 3) _counter = 2;
		AudioManager::get()->PlaySoundW(SFX::switchButton1);
		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1));
		//gObj->scale(glm::vec3(1, 1.0f, 2.0f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !_isKeyPress) {
		_isKeyPress = true;
		if (_counter == 2) _counter++;
		if (_counter == 0) _counter++;
		AudioManager::get()->PlaySoundW(SFX::switchButton1);
		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1));
		//gObj->scale(glm::vec3(1, 1.0f, 2.0f));
	}
	
	else if(_isKeyPress){
		_delayCounter++;
		if (_delayCounter == _delay) {
			_delayCounter = 0;
			_isKeyPress = false;
		}
	}
}



void StartState::_clearObjectColor() {
	for (int i = 0; i < 4; i++) {
		if (i == _counter) continue;
		GameObject* gObj = _selectableObjs[i];
		gObj->getMaterial()->setColor(glm::vec3(0));

		//gObj->scale(glm::vec3(1, 1, 0.5f));
	}
}

void StartState::deleteScene() {
	World::remove(_plane);
	World::remove(_selectableObjs[0]);
	World::remove(_selectableObjs[1]);
	World::remove(_selectableObjs[2]);
	World::remove(_selectableObjs[3]);
	delete _plane;
	delete _selectableObjs[0];
	delete _selectableObjs[1];
	delete _selectableObjs[2];
	delete _selectableObjs[3];
}

StartState::~StartState()
{
	//dtor
}
