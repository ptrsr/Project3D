#include "../network/scene/SyncScene.hpp"

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

#include "mge/config.hpp"

#include "../network/TestData.hpp"

SyncScene* SyncScene::instance = 0;

SyncScene::SyncScene() : AbstractGame()
{
	instance = this;
}


SyncScene::~SyncScene()
{
	
}

void SyncScene::initialize() {
	//setup the core part
	AbstractGame::initialize();
}

//build the game _world
void SyncScene::_initializeScene()
{
	_renderer->setClearColor(0, 0, 0);

	Camera* camera = new Camera("camera", glm::vec3(0, 2, 10));
	_world->add(camera);
	_world->setMainCamera(camera);

	Mesh* mCube = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
	ColorMaterial* cMat = new ColorMaterial(glm::vec3(1, 1, 1));

	gCube = new GameObject("Cube", glm::vec3(0, 0, 0));
	gCube->setMesh(mCube);
	gCube->setMaterial(cMat);
	gCube->setBehaviour(new KeysBehaviour(-5.0f, 90.0f));
	_world->add(gCube);

	server = new Server(8888, 4);
	thread tServer(&Server::StartServer, server);
	tServer.detach();
}

void SyncScene::_render() {
	AbstractGame::_render();


	glm::vec3 pos = gCube->getLocalPosition();
	glm::vec3 rot = gCube->getTransform()[1];

	TestData testData;

	testData.t = 0;
	testData.r = 0;
	testData.g = 0;
	testData.b = 0;
	testData.a = 0;

	testData.pX = 5.0f;
	testData.pY = 5.0f;
	testData.pZ = 5.0f;

	testData.rX = rot.x;
	testData.rY = rot.y;
	testData.rZ = rot.z;
	
	server->Send(DataType::TESTDATA, (char*)&testData);
}