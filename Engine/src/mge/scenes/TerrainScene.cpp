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

#include "mge/util/DebugHud.hpp"

#include "mge/config.hpp"
#include "mge/scenes/TerrainScene.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
TerrainScene::TerrainScene():AbstractGame (),_hud(0)
{
}

void TerrainScene::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part
	cout << "Initializing HUD" << endl;
	_hud = new DebugHud(_window);
	cout << "HUD initialized." << endl << endl;
}

//build the game _world
void TerrainScene::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);

	///CAMERA
	Camera* camera = new Camera();
	_world->add(camera);
	_world->setMainCamera(camera);

	///TERRAIN
	GameObject* terrain = new GameObject("terrain");
	terrain->setMesh(Mesh::load(config::MGE_MODEL_PATH + "plane_8192.obj"));
	
	TerrainMaterial* terMat = new TerrainMaterial("heightmap.png", "diffuse1.jpg", "water.jpg", "diffuse3.jpg", "diffuse4.jpg", "splatmap.png");
	//TerrainMaterial* terMat = new TerrainMaterial("heightmap2.png", "diffuse1.jpg", "diffuse2.jpg", "diffuse3.jpg", "diffuse4.jpg", "splatmap2.png");
	terMat->enableWater(true, 2);
	terrain->setMaterial(terMat);

	camera->setBehaviour(new OrbitBehaviour(terrain, 3));

	///LIGHT
	GameObject* light = new GameObject("light");
	light->setBehaviour(new DirectionalLight(glm::vec3(1), glm::vec3(0.1f), glm::vec3(1)));
	light->rotate(glm::pi<float>() * 0.25f, glm::vec3(1, 0, 0));

	_world->add(terrain);

	//GameObject* pLightRotor = new GameObject("pLightRotor");
	//pLightRotor->setBehaviour(new RotatingBehaviour(glm::vec3(1,0,0)));
	//_world->add(pLightRotor);

	//GameObject* pLight = new GameObject("pLight", glm::vec3(0,2,0));
	//pLight->setMesh(Mesh::load(config::MGE_MODEL_PATH + "sphere_flat.obj", 0.2f));
	//pLight->setMaterial(new ColorMaterial(glm::vec3(1)));
	//pLight->setBehaviour(new PointLight());
	//pLight->setParent(pLightRotor);
}

void TerrainScene::_render() {
    AbstractGame::_render();
    _updateHud();
}

void TerrainScene::_updateHud() {
    string debugInfo = "";
    debugInfo += string ("FPS:") + std::to_string((int)_fps)+"\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

TerrainScene::~TerrainScene()
{
	//dtor
}
