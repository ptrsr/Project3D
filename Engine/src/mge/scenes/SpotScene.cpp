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
#include "../game/Level.hpp"

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/scenes/SpotScene.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
SpotScene::SpotScene():AbstractGame (),_hud(0)
{
}

void SpotScene::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	//cout << "Initializing HUD" << endl;
	//_hud = new DebugHud(_window);
	//cout << "HUD initialized." << endl << endl;
}

//build the game _world
void SpotScene::_initializeScene()
{
    _renderer->setClearColor(0,0,0);

	Level* level = new Level(glm::vec2(9,9));

	GameObject* spotLight = new GameObject("dirL", glm::vec3(0, 1.3f, -1));
	spotLight->setBehaviour(new DirectionalLight());
	spotLight->rotate(90, glm::vec3(1, 0, 0));
	_world->add(spotLight);

	////CAMERA
	Camera* camera = new Camera();
	_world->add(camera);
	_world->setMainCamera(camera);

	GameObject* empty = new GameObject("empty", glm::vec3(5, 0, 5));
	camera->setBehaviour(new OrbitBehaviour(empty, 10));


}

void SpotScene::_render() {
    AbstractGame::_render();
    //_updateHud();
}

void SpotScene::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
//    _hud->draw();
}

SpotScene::~SpotScene()
{
	//dtor
}
