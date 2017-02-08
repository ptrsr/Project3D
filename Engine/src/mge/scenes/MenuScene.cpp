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
    Camera* camera = new Camera ("camera", glm::vec3(0,0,0));
    _world->add(camera);
    _world->setMainCamera(camera);

	_currentState = new StartState();
	_currentState->_initializeScene();

	GameObject* empty = new GameObject("empty", glm::vec3(0, 0, 0));
	camera->setBehaviour(new OrbitBehaviour(empty, 3));
	
}

void MenuScene::_render() {
    AbstractGame::_render();
    _updateHud();
	if (_currentState != nullptr) {
		_currentState->Update();
		if (int result = _currentState->CheckSelection() != -1) {
			_changeState(result);
		}
	}
	

}

void MenuScene::_changeState(int result) {
	switch (result)
	{
	case 0:
		//_currentState = new State
		break;
	case 1:
		//_currentState = new State
		break;
	case 2:
		//_currentState = new State
		break;
	case 3: 
		//_currentState = new State
		break;
	default:
		break;
	}
	_updateHud();
	_currentState->Update();
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
