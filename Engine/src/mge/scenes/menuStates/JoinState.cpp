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


	GameObject* spotLight = new GameObject("dirL", glm::vec3(0, 1.3f, -1));
	spotLight->setBehaviour(new DirectionalLight());
	spotLight->rotate(90, glm::vec3(1, 0, 0));
	World::add(spotLight);


	_plane = new GameObject("plane", glm::vec3(-2.5f, 0, 1));
	_plane->setMesh(planeMesh);
	_plane->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
	_plane->rotate(75, glm::vec3(0, 1, 0));
	World::add(_plane);


	GameObject* writingStone = new GameObject("writingStone", glm::vec3(-2.5f, 0.2f, 1.5f));
	writingStone->rotate(75, glm::vec3(0, 1, 0));
	writingStone->scale(glm::vec3(0.2f, 0.2f, 0.5f));
	writingStone->setMesh(cubeMesh);
	writingStone->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
	World::add(writingStone);
	_selectableObjs[1] = writingStone;

	GameObject* rock = new GameObject("rock1", glm::vec3(-2.0f, 0.2f, 0.5f));
	rock->rotate(75, glm::vec3(0, 1, 0));
	rock->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	rock->setMesh(cubeMesh);
	rock->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
	World::add(rock);
	_selectableObjs[0] = rock;

	
}
//Update called outside of the class
void JoinState::Update() {
	_inAnotherState = false;
	_updateColor();
}

//check if you selected
int JoinState::CheckSelection() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !_isKeyPress) {
		_inAnotherState = true;
		_isKeyPress = true;
		if (_counter = 1) return 0;
		return -1;
	}
	else return 0;
}

//Gets the object to use as the LookAt object of the camera
GameObject* JoinState::getPlane() {
	return _plane;
}

//Clears and updates the color of the object you are currently on(applies some delay for keyDown like behaviour)
void JoinState::_updateColor() {
	if (_inAnotherState) return;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !_isKeyPress) {
		_isKeyPress = true;
		_counter--;
		if (_counter < 0) _counter = 1;

		cout << "Selection: " << _counter << endl;
		_clearObjectColor();
		GameObject* gObj = _selectableObjs[_counter];
		gObj->getMaterial()->setColor(glm::vec3(1, 1, 1));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !_isKeyPress) {
		_isKeyPress = true;
		_counter++;
		if (_counter > 1) _counter = 0;

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


//Clear objectsColor
void JoinState::_clearObjectColor() {
	GameObject* gObj = _selectableObjs[0];
	gObj->getMaterial()->setColor(glm::vec3(1, 0, 1));
	GameObject* gObj2 = _selectableObjs[1];
	gObj2->getMaterial()->setColor(glm::vec3(1, 0, 1));
}

void JoinState::deleteScene() {
	World::remove(_plane);
	World::remove(_selectableObjs[0]);
	World::remove(_selectableObjs[1]);
	delete _plane;
	delete _selectableObjs[0];
	delete _selectableObjs[1];
}

JoinState::~JoinState()
{

}
