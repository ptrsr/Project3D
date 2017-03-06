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

	_counter++;
	if (_counter >= _waitTime) {
		_finished = true;
	}
}
//check if you selected
int WinState::CheckSelection() {
	if (_finished) return -1;
	else { return 4; };
	
}

void WinState::spawnRanking() {

	float _score[4];
	_score[0]= Level::get()->getScoreOfId(0);
	_score[1] = Level::get()->getScoreOfId(1);
	_score[2] = Level::get()->getScoreOfId(2);
	_score[3] = Level::get()->getScoreOfId(3);
	float highestScore = 0;
	int id = -1;

	//Setting first Position
	for (int i = 0; i < 4; i++)
	{
		if (highestScore < _score[i])
		{
			highestScore = _score[i];
			id = i + 1;
		}
	}
	_score[id - 1] = 0;
	highestScore = 0;
	_firstPos = new GameObject("one", getStatue(id));
	if (_firstPos == NULL) {
		cout << "Couldn't find statue to set rank" << endl;
		return;
	}
	id = -1;
	_firstPos->setMesh(_oneBig);
	_firstPos->translate(glm::vec3(0, 1.5f, 0));
	_firstPos->rotateDegrees(180, glm::vec3(0, 1, 0));
	_firstPos->setMaterial(new LitMaterial());
	World::add(_firstPos);

	//Setting Second Position
	for (int i = 0; i < 4; i++)
	{
		if (highestScore < _score[i])
		{
			highestScore = _score[i];
			id = i + 1;
		}
	}
	_score[id - 1] = 0;
	highestScore = 0;
	_secondPos = new GameObject("two", getStatue(id));
	if (_secondPos == NULL) {
		cout << "Couldn't find statue to set rank" << endl;
		return;
	}
	id = -1;
	_secondPos->setMesh(_twoBig);
	_secondPos->translate(glm::vec3(0, 1.5f, 0));
	_secondPos->rotateDegrees(180,glm::vec3(0, 1, 0));
	_secondPos->setMaterial(new LitMaterial());
	World::add(_secondPos);

	//Setting Third Position
	for (int i = 0; i < 4; i++)
	{
		if (highestScore < _score[i])
		{
			highestScore = _score[i];
			id = i + 1;
		}
	}
	_score[id - 1] = 0;
	highestScore = 0;
	_thirdPos = new GameObject("three", getStatue(id));
	if (_thirdPos == NULL) {
		cout << "Couldn't find statue to set rank" << endl;
		return;
	}
	id = -1;
	_thirdPos->setMesh(_threeBig);
	_thirdPos->translate(glm::vec3(0, 1.5f, 0));
	_thirdPos->rotateDegrees(180, glm::vec3(0, 1, 0));
	_thirdPos->setMaterial(new LitMaterial());
	World::add(_thirdPos);

	//Setting Fourth Position
	for (int i = 0; i < 4; i++)
	{
		if (highestScore < _score[i])
		{
			highestScore = _score[i];
			id = i + 1;
		}
	}
	_score[id - 1] = 0;
	highestScore = 0;
	_forthPos = new GameObject("four",getStatue(id));
	if (_forthPos == NULL) {
		cout << "Couldn't find statue to set rank" << endl;
		return;
	}

	id = -1;
	_forthPos->setMesh(_fourBig);
	_forthPos->translate(glm::vec3(0, 1.5f, 0));
	_forthPos->rotateDegrees(180, glm::vec3(0, 1, 0));
	_forthPos->setMaterial(new LitMaterial());
	World::add(_forthPos);
	
	_spawned = true;
	
}

glm::vec3 WinState::getStatue(int playerId) {
	if (playerId == 1) {
		return ObjectCache::find("Fire1")->getLocalPosition();
	}
	else if (playerId == 2) {
		return ObjectCache::find("Earth1")->getLocalPosition();
	}
	else if (playerId == 3) {
		return ObjectCache::find("Water1")->getLocalPosition();
	}
	else if (playerId == 4) {
		return ObjectCache::find("Wind1")->getLocalPosition();
	}
	else {
		return glm::vec3(0,0,0);
	}

}

//Gets the object to use as the LookAt object of the camera
GameObject* WinState::getPlane() {
	return _plane;
}

void WinState::deleteScene() {
}

WinState::~WinState()
{

}
