#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

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

	GameObject* spotLight = new GameObject("dirL", glm::vec3(0, 1.3f, -1));
	spotLight->setBehaviour(new DirectionalLight());
	spotLight->rotate(90, glm::vec3(1, 0, 0));
	World::add(spotLight);


	GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
	plane->setMesh(planeMesh);
	plane->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
	World::add(plane);

	for (int i = 0; i < 4; i++) {
		GameObject* rock = new GameObject("rock1", glm::vec3((i * 0.5f) - 0.75f, 0.2f, 0));
		rock->scale(glm::vec3(0.2f, 0.2f, 0.2f));
		rock->setMesh(cubeMesh);
		rock->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
		World::add(rock);
		_selectableObjs[i] = rock;
	}

	
}

void StartState::Update() {
	_updateColor();
}

int StartState::CheckSelection() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		return _counter;
	}
	else return -1;
}


void StartState::_updateColor() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isKeyPress) {
		_isKeyPress = true;
		_counter--;
		if (_counter < 0) _counter = 3;

		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1, 1, 1));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isKeyPress) {
		_isKeyPress = true;
		_counter++;
		if (_counter > 3) _counter = 0;

		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1, 1, 1));
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
		gObj->getMaterial()->setColor(glm::vec3(1, 0, 1));
	}
}

StartState::~StartState()
{
	//dtor
}
