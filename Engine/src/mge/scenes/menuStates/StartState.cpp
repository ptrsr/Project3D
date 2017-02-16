#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"
#include "mge/auxiliary/ObjectCache.hpp"

#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials//LitMaterial.hpp"
#include "mge/materials/TerrainMaterial.hpp"

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
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	//GameObject* spotLight = new GameObject("dirL", glm::vec3(0, 1.3f, -1));
	//spotLight->setBehaviour(new DirectionalLight());
	//spotLight->rotate(90, glm::vec3(1, 0, 0));
	//World::add(spotLight);


	GameObject * plane = ObjectCache::find("StartPlane");
	if (plane != NULL) {
		_plane = plane;
		
	}

	/*for (int i = 0; i < 4; i++) {
		GameObject* rock = new GameObject("rock1", glm::vec3((i * 0.5f) - 0.75f, 0.2f, 20));
		rock->scale(glm::vec3(0.2f, 0.2f, 0.2f));
		rock->setMesh(cubeMesh);
		rock->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
		World::add(rock);
		_selectableObjs[i] = rock;
	}*/
	GameObject * create = ObjectCache::find("create_text");
	if (create != NULL)
	{
		_selectableObjs[0] = create;

	}
	GameObject * credits = ObjectCache::find("credits_text");
	if (credits != NULL)
	{
		_selectableObjs[1] = credits;

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
		else if (_selectableObjs[_counter]->getName() == "credits_text") {

			return 1;
		}
	}
	else return -1;
}


void StartState::_updateColor() {
	if (_inAnotherState) return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isKeyPress) {
		_isKeyPress = true;
		_counter--;
		if (_counter < 0) _counter = 1;

		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1, 0, 0));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isKeyPress) {
		_isKeyPress = true;
		_counter++;
		if (_counter > 1) _counter = 0;

		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1, 0, 0));
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
	for (int i = 0; i < 2; i++) {
		if (i == _counter) continue;
		GameObject* gObj = _selectableObjs[i];
		gObj->getMaterial()->setColor(glm::vec3(1, 1, 1));
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
