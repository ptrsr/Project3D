#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/core/GameObject.hpp"
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

#include "mge/auxiliary/LuaParser.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/scenes/UnityScene.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
UnityScene::UnityScene():AbstractGame (),_hud(0)
{
}

void UnityScene::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void UnityScene::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);

	Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
	_world->add(camera);
	_world->setMainCamera(camera);

	LuaParser* luaParser = new LuaParser("main.lua");

	GameObject* empty = new GameObject("Empty");
	_world->add(empty);
	camera->setBehaviour(new OrbitBehaviour(empty, 400));
}

void UnityScene::_render() {
    AbstractGame::_render();
    _updateHud();
}

void UnityScene::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

UnityScene::~UnityScene()
{
	//dtor
}
