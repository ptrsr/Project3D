#include <glm.hpp>
#include <iostream>
#include <string>
using namespace std;

#include "mge/core/Renderer.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/core/World.hpp"

#include "mge/core/Camera.hpp"

#include "mge/auxiliary/ObjectCache.hpp"
#include "mge/auxiliary/AudioManager.h"

#include "mge/materials/AbstractMaterial.hpp"

#include "mge/materials/ColorMaterial.hpp"
#include "mge/materials/TextureMaterial.hpp"
#include "mge/materials/WobbleMaterial.hpp"
#include "mge/materials//LitMaterial.hpp"

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
#include "mge/scenes/menuStates/WinState.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
WinState::WinState()
{
}
//Sets the scene for the credits
void WinState::_initializeScene()
{

	_oneBig = Mesh::load(config::MGE_MODEL_PATH + "one_big.obj");
	_twoBig = Mesh::load(config::MGE_MODEL_PATH + "two_big.obj");
	_threeBig = Mesh::load(config::MGE_MODEL_PATH + "three_big.obj");
	_fourBig = Mesh::load(config::MGE_MODEL_PATH + "four_big.obj");





	GameObject * plane = ObjectCache::find("winPlane");
	if (plane != NULL) {
		_plane = plane;
	}

}
//Update called outside of the class
void WinState::Update() {
	if (!_spawned)
		spawnRanking();

	if (_counter >= _waitTime) {
		_finished = true;
	}
	else {
		_counter++;
		_waitTime = 500;
	}
}
//check if you selected
int WinState::CheckSelection() {
	if (_finished) {
		_finished = false;
		_counter = 0;
		_spawned = false;
		return -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
		_finished = false;
		_counter = 0;
		_spawned = false;
		return -1;
	}
	else { return 4; };
	
}

Id WinState::GetHighestScore(float* scores)
{
	float highestScore = -1;
	int id = -1;

	for (int i = 0; i < 4; i++)
	{
		if (highestScore < scores[i])
		{
			highestScore = scores[i];
			id = i + 1;
		}
	}
	scores[id - 1] = -1;

	return (Id)id;
}

void WinState::AddNumberObj(Id playerId, int place)
{
	GameObject* placeNumber = new GameObject("placeNumber" + place, glm::vec3(0, 0, 0));
	placeNumber->setMesh(GetNumberMesh(place));
	placeNumber->translate(glm::vec3(0, 1.5f, 0));
	placeNumber->setMaterial(new LitMaterial());
	placeNumber->setParent(getStatue(playerId));
	_numbers.push_back(placeNumber);
}

Mesh* WinState::GetNumberMesh(int place)
{
	switch (place)
	{
	case 1:
		return _oneBig;
	case 2:
		return _twoBig;
	case 3:
		return _threeBig;
	case 4:
		return _fourBig;
	}
}

void WinState::spawnRanking()
{
	float scores[4];
	for (int i = 0; i < 4; i++)
	{
		scores[i] = Level::get()->getScoreOfId(i);
	}

	Id first = GetHighestScore(scores);
	Id second = GetHighestScore(scores);
	Id third = GetHighestScore(scores);
	Id fourth = GetHighestScore(scores);

	AddNumberObj(first, 1);
	AddNumberObj(second, 2);
	AddNumberObj(third, 3);
	AddNumberObj(fourth, 4);
	
	_spawned = true;
}

GameObject* WinState::getStatue(int playerId) {
	if (playerId == Id::p1) {
		return ObjectCache::find("Fire1");
	}
	else if (playerId == Id::p2) {
		return ObjectCache::find("Earth1");
	}
	else if (playerId == Id::p3) {
		return ObjectCache::find("Water1");
	}
	else if (playerId == Id::p4) {
		return ObjectCache::find("Wind1");
	}
	else {
		return NULL;
	}

}

//Gets the object to use as the LookAt object of the camera
GameObject* WinState::getPlane() {
	return _plane;
}

void WinState::deleteScene()
{
	while (_numbers.size() > 0)
	{
		delete _numbers[0];
		_numbers.erase(_numbers.begin());
	}
}

WinState::~WinState()
{
	
}
