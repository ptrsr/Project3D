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
    Camera* camera = new Camera ("camera", glm::vec3(0,2,3));
    _world->add(camera);
    _world->setMainCamera(camera);


	_startState = new StartState();
	_startState->_initializeScene();

	_joinState = new JoinState();
	_joinState->_initializeScene();

	_creditsState = new CreditsState();
	_creditsState->_initializeScene();


	_currentState = -1;


	GameObject* empty = new GameObject("empty", glm::vec3(0, 0, 0));
	camera->setBehaviour(new LookAt(_startState->getPlane()));
	
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
				_cameraStateChanged = true;
			}
			if (_currentState != -1) _cameraStateChanged = false;
			break;
		case 0:
			_joinState->Update();
			_currentState = _joinState->CheckSelection();
			if (!_cameraStateChanged) {
				_changeCameraState(_joinState);
				_cameraStateChanged = true;
			}
			if (_currentState != 0) _cameraStateChanged = false;
			break;

		case 2:
			_creditsState->Update();
			_currentState = _creditsState->CheckSelection();
			if (!_cameraStateChanged) {
				_changeCameraState(_creditsState);
				_cameraStateChanged = true;
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
		GameObject* plane = state->getPlane();
		if (plane != nullptr) {
			Camera * camera = _world->getMainCamera();
			camera->setBehaviour(new LookAt(plane));
			_cameraStateChanged = true;
		}
}

void MenuScene::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";
    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}
MenuScene::~MenuScene()
{
	//dtor
}
