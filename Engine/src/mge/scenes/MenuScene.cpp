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
#include "mge/auxiliary/LuaParser.hpp"
#include "mge/auxiliary/GameTimer.hpp"


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
}
//build the game _world
void MenuScene::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);
    Camera* camera = new Camera (glm::vec2(1200, 720),"camera", glm::vec3(-4.5f,2,28));
	camera->rotateDegrees(180, glm::vec3(0, 1, 0));
    _world->add(camera);
    _world->setMainCamera(camera);



	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;


	_gameTimer = new GameTimer();
	_gameTimer->_initializeScene();
	_gameTimer->setTimeLenght(2.5f);

	AudioManager::get();


	LuaParser* luaParser = new LuaParser("main.lua");

	GameObject* center = new GameObject("center");
	GameObject* holder = new GameObject("holder");
	GameObject* light = new GameObject("light");

	holder->setBehaviour(new OrbitBehaviour(center, 1, sf::Mouse::Button::Right));

	light->setBehaviour(new DirectionalLight(glm::vec3(1), glm::vec3(0.1f)));
	light->setParent(holder);



	_startState = new StartState();
	_startState->_initializeScene();

	_joinState = new JoinState();
	_joinState->_initializeScene();

	_creditsState = new CreditsState();
	_creditsState->_initializeScene();

	_text = new Text(TextType::IP);
	_text->_initializeScene();


	Level::get();

	_currentState = -1;
	_world->add(center);
	_world->add(holder);

	
}

void MenuScene::_render() {
    AbstractGame::_render();
    _updateHud();

	if (_startState != nullptr && _joinState != nullptr && _creditsState != nullptr) {

		_text->Update();
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

				AudioManager::get()->PlaySound(SFX::enterButton1);
				_changeCameraState(_joinState);
					cout << "camera state changed" << endl;
			}
			if (_currentState != 2) _cameraStateChanged = false;
			break;

		case 3:

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
				_currentState = -1;
				AudioManager::get()->PlaySound(SFX::backButton1);
				Level::reset();
			}
			if (!_cameraStateChanged) {
				AudioManager::get()->PlaySound(SFX::enterButton1);
				cout << "camera state changed" << endl;
				_changeCameraState(_level);
			}
			if (_currentState != 3) _cameraStateChanged = false;
			break;

		case 1:

			cout << "Credits" << endl;
			_creditsState->Update();

			_currentState = _creditsState->CheckSelection();
			if (!_cameraStateChanged) {
				AudioManager::get()->PlaySound(SFX::enterButton1);
				_changeCameraState(_creditsState);
			}
			if (_currentState != 1) _cameraStateChanged = false;
			break;

		case 0:
			
			_window->close();
			
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
			camera->setBehaviour(new CameraBehaviour(plane));
			_cameraStateChanged = true;
		}
}
void MenuScene::_changeCameraState(Level* level) {
	GameObject* empty = new GameObject("empty", glm::vec3(0,0,0));
	GameObject * plane = ObjectCache::find("playPlane");
	if (plane != NULL) {
		empty = plane;

	}
		Camera * camera = _world->getMainCamera();
		camera->setBehaviour(new CameraBehaviour(empty));

		_cameraStateChanged = true;
}

void MenuScene::_updateHud() {

	string debugInfo = "";
	debugInfo += string("FPS:") + std::to_string((int)_fps) + "\n";
	debugInfo += string("                 Player1 score: " + std::to_string((int)Level::get()->getPlayers()[0]->getScore())+ "\n");
	debugInfo += string("                 Player2 score: " + std::to_string((int)Level::get()->getPlayers()[1]->getScore())+ "\n");

	_hud->setDebugInfo(debugInfo);
	_hud->draw();
}
MenuScene::~MenuScene()
{
	//dtor
}
