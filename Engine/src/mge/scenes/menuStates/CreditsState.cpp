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
#include "mge/scenes/menuStates/CreditsState.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
CreditsState::CreditsState()
{
}
//build the game _world
void CreditsState::_initializeScene()
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");

	GameObject * plane = ObjectCache::find("JoinPlane");
	if (plane != NULL) {
		_plane = plane;
	}

	GameObject * back = ObjectCache::find("back_text");
	if (back != NULL)
	{
		_selectableObj = back;
	}

	//_writingStone = new GameObject("writingStone", glm::vec3(-2.5f, 0.2f, 18.5f));
	//_writingStone->rotate(-75, glm::vec3(0, 1, 0));
	//_writingStone->scale(glm::vec3(0.2f, 0.3f, 0.3f));
	//_writingStone->setMesh(cubeMesh);
	//_writingStone->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
	//World::add(_writingStone);

	//_selectableObj = new GameObject("rock1", glm::vec3(-2.5f, 0.2f, 19.5f));
	//_selectableObj->rotate(-75, glm::vec3(0, 1, 0));
	//_selectableObj->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	//_selectableObj->setMesh(cubeMesh);
	//_selectableObj->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 1, 1)));
	//World::add(_selectableObj);

	
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

void CreditsState::_updateColor() {}

int CreditsState::CheckSelection() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !_isKeyPress) {
		cout << "Going back to start" << endl;
		_isKeyPress = true;
		_inAnotherState = true;
		return -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_isKeyPress) {
		cout << "Going back to start" << endl;
		_isKeyPress = true;
		_inAnotherState = true;
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
