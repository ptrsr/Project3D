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

#include "mge/behaviours/CameraBehaviour.hpp"

#include "mge/behaviours/DirectionalLight.hpp"
#include "mge/behaviours/PointLight.hpp"
#include "mge/behaviours/SpotLight.hpp"
#include "../game/Level.hpp"

#include "mge/util/DebugHud.hpp"
#include "mge/util/InputHandler.h"

#include "mge/scenes/menuStates/StartState.hpp"
#include "mge/scenes/menuStates/JoinState.hpp"
#include "mge/scenes/menuStates/CreditsState.hpp"

#include "mge/config.hpp"
#include "mge/scenes/MenuScene.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
MenuScene::MenuScene():AbstractGame (),_hud(0)
{
}

void MenuScene::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}
//build the game _world
void MenuScene::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);
    Camera* camera = new Camera (glm::vec2(1200, 720),"camera", glm::vec3(0,1,17));
	camera->rotateDegrees(180, glm::vec3(0, 1, 0));
    _world->add(camera);
    _world->setMainCamera(camera);


	_startState = new StartState();
	_startState->_initializeScene();

	_joinState = new JoinState();
	_joinState->_initializeScene();

	_creditsState = new CreditsState();
	_creditsState->_initializeScene();

	_currentState = -1;

	Level::get();
	
}

void MenuScene::_render() {
    AbstractGame::_render();
    _updateHud();
	if (_startState != nullptr && _joinState != nullptr && _creditsState != nullptr) {
		switch (_currentState) {
		case -1:
			_startState->Update();
			_currentState = _startState->CheckSelection();
			if (!_cameraStateChanged) {
				_changeCameraState(_startState);
			}
			if (_currentState != -1) _cameraStateChanged = false;
			break;
		case 2:
			_joinState->Update();
			_currentState = _joinState->CheckSelection();
			if (!_cameraStateChanged) {
				_changeCameraState(_joinState);
					cout << "camera state changed" << endl;
			}
			if (_currentState != 2) _cameraStateChanged = false;
			break;

		case 3:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				_currentState = -1;
			}
			if (!_cameraStateChanged) {

				Level::get()->Host();
				//Level::get()->Join("127.0.0.1", 8888);

				cout << "camera state changed" << endl;
				_changeCameraState(_level);
			}
			if (_currentState != 3) _cameraStateChanged = false;
			break;

		case 1:
			_creditsState->Update();
			_currentState = _creditsState->CheckSelection();
			if (!_cameraStateChanged) {
				_changeCameraState(_creditsState);
			}
			if (_currentState != 1) _cameraStateChanged = false;
			break;

	}
	}
	

}
void MenuScene::_deleteScene() {
	delete _newState;
}


void MenuScene::_changeCameraState(AbstactState* state) {
		GameObject* plane = new GameObject("empty",glm::vec3(0,0,0));
		plane->setTransform(state->getPlane()->getTransform());

		plane->translate(glm::vec3(0,2,5));
		if (plane != nullptr) {
			Camera * camera = _world->getMainCamera();
			camera->setBehaviour(new CameraBehaviour(plane));
			_cameraStateChanged = true;
		}
}
void MenuScene::_changeCameraState(Level* level) {
		GameObject* empty = new GameObject("empty", glm::vec3(4, 6, -4));
		empty->rotateDegrees(180, glm::vec3(0, 1, 0));

		empty->rotateDegrees(-45, glm::vec3(1, 0, 0));
		Camera * camera = _world->getMainCamera();
		camera->setBehaviour(new CameraBehaviour(empty));

		_cameraStateChanged = true;
}

void MenuScene::_updateHud() {
}
MenuScene::~MenuScene()
{
	//dtor
}
