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

#include "mge/behaviours/RotatingBehaviour.hpp"
#include "mge/behaviours/KeysBehaviour.hpp"
#include "mge/behaviours/LookAt.hpp"
#include "mge/behaviours/OrbitBehaviour.hpp"
#include "mge/behaviours/CameraBehaviour.hpp"

#include "mge/behaviours/DirectionalLight.hpp"
#include "mge/behaviours/PointLight.hpp"
#include "mge/behaviours/SpotLight.hpp"

#include "mge/auxiliary/LuaParser.hpp"
#include "mge/auxiliary/ObjectCache.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/scenes/ObjectViewer.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
ObjectViewer::ObjectViewer():AbstractGame (),_hud(0)
{
}

void ObjectViewer::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void ObjectViewer::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);

	Camera* camera = new Camera(glm::vec2(1280,720),"camera",glm::vec3(15,10,15));
	_world->add(camera);
	_world->setMainCamera(camera);

	LuaParser* luaParser = new LuaParser("main.lua");

	GameObject* center = new GameObject("center");
	GameObject* holder = new GameObject("holder");
	GameObject* light = new GameObject("light");

	holder->setBehaviour(new OrbitBehaviour(center, 1, sf::Mouse::Button::Right));

	light->setBehaviour(new DirectionalLight(glm::vec3(1), glm::vec3(0.1f)));
	light->setParent(holder);

/*
	GameObject* empty = new GameObject("empty",glm::vec3(0,0,0));
	camera->setBehaviour(new OrbitBehaviour(empty, 5));*/


	GameObject* plane = ObjectCache::find("Plane");
	GameObject* cube = ObjectCache::find("Cube");
	if (cube != NULL) {
		cube->scale(glm::vec3(4.5f, 0, 4.5f));
	}
	if (plane != NULL) {
		/*plane->rotateDegrees(45, glm::vec3(0, 1, 0));
		plane->rotateDegrees(45, glm::vec3(0, 0, 1));*/
		camera->setBehaviour(new OrbitBehaviour(plane,20));
	}
	else {
		cout << "Camera behaviour is not set" << endl;
	}

	_world->add(center);
	_world->add(holder);
}

void ObjectViewer::_render() {
    AbstractGame::_render();
    _updateHud();
}

void ObjectViewer::_updateHud() {/*
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();*/
}

ObjectViewer::~ObjectViewer()
{
	//dtor
}
