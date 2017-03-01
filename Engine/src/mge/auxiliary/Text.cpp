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
#include "mge/auxiliary/Text.hpp"


//construct the game class into _window, _renderer and hud (other parts are initialized by build)
Text::Text(TextType textType)
{
	_textType = textType;
}
//Sets the scene for the credits
void Text::_initializeScene()
{
	Mesh* planeMesh = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
	Mesh* cubeMesh = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");


	GameObject * create = ObjectCache::find("create_text");
	if (create != NULL)
	{
		placeToRenderText = create;
	}


	//GameObject* writingStone = new GameObject("writingStone", glm::vec3(3.0f, 0.2f, 18.5f));
	//writingStone->rotate(75, glm::vec3(0, 1, 0));
	//writingStone->scale(glm::vec3(0.2f, 0.2f, 0.5f));
	//writingStone->setMesh(cubeMesh);
	//writingStone->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
	//World::add(writingStone);
	//_selectableObjs[1] = writingStone;
	//GameObject* rock = new GameObject("rock1", glm::vec3(2.5f, 0.2f, 19.5f));
	//rock->rotate(75, glm::vec3(0, 1, 0));
	//rock->scale(glm::vec3(0.2f, 0.2f, 0.2f));
	//rock->setMesh(cubeMesh);
	//rock->setMaterial(new LitMaterial(LitMaterial::Lit::fragment, glm::vec3(1, 0, 1)));
	//World::add(rock);
	//_selectableObjs[0] = rock;

	
}
//Update called outside of the class
void Text::Update() {
	if (_textType == TextType::IP) {
		_updateIP();
	}
	if (_textType == TextType::Score) {
		_updateScore();
	}
	if (_textType == TextType::DisplayNormal) {
		_updateDisplay();
	}
}

//check if you selected
int Text::CheckSelection() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !_isKeyPress) {
		_isKeyPress = true;

		 return -1;
	}
	else return 2;
}

//Gets the object to use as the LookAt object of the camera
GameObject* Text::getPlane() {
	return placeToRenderText;
}

void Text::setText(string textToDislpay) {
	_textToDislplay = textToDislpay;
}

//Clears and updates the color of the object you are currently on(applies some delay for keyDown like behaviour)
void Text::_updateIP() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && !_isKeyPress)
	{
		if (text.size() == 0) return;
		deleteLastObject();
		text.erase(text.size() - 1);
		_isKeyPress = true;
		cout << text << endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) && !_isKeyPress)
	{
		
		_isKeyPress = true;
		cout << text << endl;
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) && !_isKeyPress)
	{
		text += "0";
		_isKeyPress = true;
		cout << text << endl;
		createObject('0');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !_isKeyPress)
	{
		text += "1";
		
		_isKeyPress = true;
		cout << text << endl;

		createObject('1');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !_isKeyPress)
	{
		text += "2";
		_isKeyPress = true;
		cout << text << endl;
		createObject('2');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !_isKeyPress)
	{
		text += "3";
		_isKeyPress = true;
		cout << text << endl;
		createObject('3');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !_isKeyPress)
	{
		text += "4";
		_isKeyPress = true;
		cout << text << endl;
		createObject('4');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !_isKeyPress)
	{
		text += "5";
		_isKeyPress = true;
		cout << text << endl;
		createObject('5');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && !_isKeyPress)
	{
		text += "6";
		_isKeyPress = true;
		cout << text << endl;
		createObject('6');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && !_isKeyPress)
	{
		text += "7";
		_isKeyPress = true;
		cout << text << endl;
		createObject('7');
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && !_isKeyPress)
	{
		text += "8";
		_isKeyPress = true;
		cout << text << endl;
		createObject('8');
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && !_isKeyPress)
	{
		text += "9";
		_isKeyPress = true;
		cout << text << endl;
		createObject('9');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period) && !_isKeyPress) {

		text += ".";
		_isKeyPress = true;
		cout << text << endl;
		createObject('.');
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon) &&
			 (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || 
			 sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && !_isKeyPress) {
		text += ":";
		_isKeyPress = true;
		cout << text << endl;
		createObject(':');

	}
	else if (_isKeyPress) {
		_delayCounter++;
		if (_delayCounter == _delay) {
			_delayCounter = 0;
			_isKeyPress = false;
		}
	}

	
	
}

void Text::_updateScore() {
	cout << "000" << endl;
	if (_isKeyPress) {
		_delayCounter++;
		if (_delayCounter == _delay) {
			_delayCounter = 0;
			_isKeyPress = false;
		}
	}
}
void Text::_updateDisplay() {
	cout << _textToDislplay << endl;
	if (_isKeyPress) {
		_delayCounter++;
		if (_delayCounter == _delay) {
			_delayCounter = 0;
			_isKeyPress = false;
		}
	}
}

void Text::createObject(char obj) {

	glm::vec3 pos = placeToRenderText->getLocalPosition();
	pos = glm::vec3(pos.x - 0.5f, pos.y, pos.z - 2);

	GameObject* toBeCreated; 
	switch (obj) {
	case '0':
		toBeCreated = new GameObject("Zero" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "zero.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		break;
	case '1':

		toBeCreated = new GameObject("One" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "one.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 1" << endl;
		break;
	case '2':
		toBeCreated = new GameObject("Two" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "two.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 2" << endl;
		break;
	case '3':
		toBeCreated = new GameObject("Three" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "three.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 3" << endl;
		break;
	case '4':
		toBeCreated = new GameObject("Four" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "four.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 4" << endl;
		break;
	case '5':
		toBeCreated = new GameObject("Five" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "five.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 5" << endl;
		break;
	case '6':
		toBeCreated = new GameObject("Six" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "six.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 6" << endl;
		break;
	case '7':
		toBeCreated = new GameObject("Seven" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "seven.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 7" << endl;
		break;
	case '8':
		toBeCreated = new GameObject("Eight" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "eight.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 8" << endl;
		break;
	case '9':
		toBeCreated = new GameObject("Nine" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "nine.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 9" << endl;
		break;
	case '.':
		toBeCreated = new GameObject("Dot" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "dot.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create ." << endl;
		break;
	case ':':
		toBeCreated = new GameObject("DoubleDot" + text.size(), glm::vec3(pos.x - text.size() * 0.2f, pos.y, pos.z));
		cout << "Create 0" << endl;
		toBeCreated->rotateDegrees(180, glm::vec3(0, 1, 0));
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "doubledot.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create :" << endl;
		break;
	default:
		cout << "Problem with creation of text character (Text.cpp,line 266)" << endl;
		break;
	}
}

void Text::deleteScene() {
}
void Text::deleteLastObject() {
	GameObject* obj = objs.at(objs.size() - 1);
	objs.pop_back();
	World::remove(obj);
	delete obj;
}

Text::~Text()
{

	//World::remove(_plane);
	//World::remove(_selectableObjs[0]);
	//World::remove(_selectableObjs[1]);
	//delete _plane;
	//delete _selectableObjs[0];
	//delete _selectableObjs[1];
}
