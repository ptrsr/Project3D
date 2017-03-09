#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/auxiliary/ObjectCache.hpp"
#include "mge/auxiliary/MeshCache.hpp"

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
#include "mge/auxiliary/GameTimer.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
GameTimer::GameTimer()
{
}
//Sets the scene for the credits
void GameTimer::_initializeScene()
{
	Mesh * zeroMesh = Mesh::load(config::MGE_MODEL_PATH + "zero.obj");
	MeshCache::push(zeroMesh);
	Mesh * oneMesh = Mesh::load(config::MGE_MODEL_PATH + "one.obj");
	MeshCache::push(oneMesh);
	Mesh * twoMesh = Mesh::load(config::MGE_MODEL_PATH + "two.obj");
	MeshCache::push(twoMesh);
	Mesh * threeMesh = Mesh::load(config::MGE_MODEL_PATH + "three.obj");
	MeshCache::push(threeMesh);
	Mesh * fourMesh = Mesh::load(config::MGE_MODEL_PATH + "four.obj");
	MeshCache::push(fourMesh);
	Mesh * fiveMesh = Mesh::load(config::MGE_MODEL_PATH + "five.obj");
	MeshCache::push(fiveMesh);
	Mesh * sixMesh = Mesh::load(config::MGE_MODEL_PATH + "six.obj");
	MeshCache::push(sixMesh);
	Mesh * sevenMesh = Mesh::load(config::MGE_MODEL_PATH + "seven.obj");
	MeshCache::push(sevenMesh);
	Mesh * eightMesh = Mesh::load(config::MGE_MODEL_PATH + "eight.obj");
	MeshCache::push(eightMesh);
	Mesh * nineMesh = Mesh::load(config::MGE_MODEL_PATH + "nine.obj");
	MeshCache::push(nineMesh);
	Mesh * doubleDotMesh = Mesh::load(config::MGE_MODEL_PATH + "doubledot.obj");
	MeshCache::push(doubleDotMesh);


	GameObject * camera =World::get()->getMainCamera();
	if (camera != NULL)
	{
		placeToRenderText = camera;
		glm::vec3 localPos = placeToRenderText->getWorldTransform()[1];
		_firstDigid = new GameObject("FirstDigid", glm::vec3(localPos.x + 1 , localPos.y, localPos.z + 2.0f));
		_firstDigid->rotateDegrees(180, glm::vec3(0, 1, 0));
		_firstDigid->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "zero.obj"));
		_firstDigid->setMaterial(new LitMaterial(glm::vec3(1)));
		World::add(_firstDigid);
		_doubleDots = new GameObject("DoubleDots", glm::vec3(localPos.x + 1.2f, localPos.y, localPos.z - 2.0f));
		_doubleDots->rotateDegrees(180, glm::vec3(0, 1, 0));
		_doubleDots->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "doubledot.obj"));
		_doubleDots->setMaterial(new LitMaterial(glm::vec3(1)));
		World::add(_doubleDots);
		_secondDigid = new GameObject("SecondDigid", glm::vec3(localPos.x + 1.4f, localPos.y, localPos.z - 2.0f));
		_secondDigid->rotateDegrees(180, glm::vec3(0, 1, 0));
		_secondDigid->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "zero.obj"));
		_secondDigid->setMaterial(new LitMaterial(glm::vec3(1)));
		World::add(_secondDigid);
		_thirdDigid = new GameObject("ThirdDigid", glm::vec3(localPos.x + 1.4f, localPos.y, localPos.z - 2.0f));
		_thirdDigid->rotateDegrees(180, glm::vec3(0, 1, 0));
		_thirdDigid->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "zero.obj"));
		_thirdDigid->setMaterial(new LitMaterial(glm::vec3(1)));
		World::add(_thirdDigid);
	}

	
}
//Update called outside of the class
void GameTimer::Update(float timeToUpdateWith) {
	_updateTimer(timeToUpdateWith);
}

void GameTimer::setTimeLenght(float minutes) {
	_minutes = minutes;
	string timer = to_string((int)_minutes) + ":" + to_string((int)std::fmod((_minutes *60), 60));
	cout << timer << endl;
	//_timer = minutes;
	//float seconds = _timer * 60;
	//float remainer = std::fmod(_timer, 60);
}

//Clears and updates the color of the object you are currently on(applies some delay for keyDown like behaviour)
void GameTimer::_updateTimer(float timeToUpdateWith) {

	_minutes = ((_minutes * 60) - timeToUpdateWith) / 60;
	string timer = to_string((int)_minutes) + ":" + to_string((int)std::fmod((_minutes * 60), 60));
	//cout << timer << endl;
	for (int i = 0; i < timer.length(); i++) {
		createObject(timer[i],i);
	}
}



void GameTimer::createObject(char obj,int digid) {

	glm::vec3 pos = placeToRenderText->getLocalPosition();
	pos = glm::vec3(pos.x - 0.5f, pos.y, pos.z - 2);

	GameObject* toBeCreated;
	if (digid == 0) {
		toBeCreated = _firstDigid;
	}
	else if (digid == 2) {

		toBeCreated = _secondDigid;
	}
	else if (digid == 3) {

		toBeCreated = _thirdDigid;
	}
	switch (obj) {
	case '0':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "zero.obj"));
		break;
	case '1':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "one.obj"));
		break;
	case '2':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "two.obj"));
		break;
	case '3':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "three.obj"));
		break;
	case '4':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "four.obj"));
		break;
	case '5':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "five.obj"));
		break;
	case '6':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "six.obj"));
		break;
	case '7':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "seven.obj"));
		break;
	case '8':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "eight.obj"));
		break;
	case '9':
		toBeCreated->setMesh(MeshCache::find(config::MGE_MODEL_PATH + "nine.obj"));
		break;
	case ':':

		//cout << ":";
		
		break;
	default:
		cout << "Problem with creation of time character (Text.cpp,line 193)" << endl;
		break;
	}
}

GameTimer::~GameTimer()
{
	
	//World::remove(_plane);
	//World::remove(_selectableObjs[0]);
	//World::remove(_selectableObjs[1]);
	//delete _plane;
	//delete _selectableObjs[0];
	//delete _selectableObjs[1];
}
