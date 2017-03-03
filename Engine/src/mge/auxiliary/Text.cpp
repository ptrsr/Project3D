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
	GameObject * create = ObjectCache::find("create_text");
	if (create != NULL)
	{
		placeToRenderText = create;
	}
	if (_textType == TextType::IP) {
		for (int i = 1; i < 24; i++) {
			std::string name = "ipNumber" + to_string(i);
			GameObject* ipSelectable = ObjectCache::find(name);
			if (ipSelectable != NULL) {
				posOfObjs[i] = ipSelectable;
			}
		}
	}
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
	}
		
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "0";
		_isKeyPress = true;
		cout << text << endl;
		createObject('0');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "1";
		
		_isKeyPress = true;
		cout << text << endl;

		createObject('1');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "2";
		_isKeyPress = true;
		cout << text << endl;
		createObject('2');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "3";
		_isKeyPress = true;
		cout << text << endl;
		createObject('3');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "4";
		_isKeyPress = true;
		cout << text << endl;
		createObject('4');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "5";
		_isKeyPress = true;
		cout << text << endl;
		createObject('5');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "6";
		_isKeyPress = true;
		cout << text << endl;
		createObject('6');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7) && !_isKeyPress)
	{

		if (text.size() == 23) return;
		text += "7";
		_isKeyPress = true;
		cout << text << endl;
		createObject('7');
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8) && !_isKeyPress)
	{
		if (text.size() == 23) return;
		text += "8";
		_isKeyPress = true;
		cout << text << endl;
		createObject('8');
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9) && !_isKeyPress)
	{
		if (text.size() == 23) return;
		text += "9";
		_isKeyPress = true;
		cout << text << endl;
		createObject('9');
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period) && !_isKeyPress) {

		if (text.size() == 23) return;
		text += ".";
		_isKeyPress = true;
		cout << text << endl;
		createObject('.');
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::SemiColon) &&
			 (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || 
			 sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) && !_isKeyPress) {

		if (text.size() == 23) return;
		text += ":";
		_isKeyPress = true;
		cout << text << endl;
		createObject(':');

	}
	else if (_isKeyPress) {
		if (_delayCounter >= _delay) {
			_delayCounter = 0;
			_isKeyPress = false;
		}
		else {
			_delayCounter++;
			_delay = 7;
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
	if (text.size() == 23) return;
	GameObject* toBeCreated; 
	switch (obj) {
	case '0':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "zero.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		break;
	case '1':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "one.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 1" << endl;
		break;
	case '2':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "two.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 2" << endl;
		break;
	case '3':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "three.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 3" << endl;
		break;
	case '4':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "four.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 4" << endl;
		break;
	case '5':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "five.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 5" << endl;
		break;
	case '6':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "six.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 6" << endl;
		break;
	case '7':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "seven.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 7" << endl;
		break;
	case '8':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "eight.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 8" << endl;
		break;
	case '9':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "nine.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create 9" << endl;
		break;
	case '.':
		toBeCreated = posOfObjs[text.size()];
		toBeCreated->setMesh(Mesh::load(config::MGE_MODEL_PATH + "dot.obj"));
		toBeCreated->setMaterial(new ColorMaterial(glm::vec3(1)));
		World::add(toBeCreated);
		objs.push_back(toBeCreated);
		cout << "Create ." << endl;
		break;
	case ':':
		toBeCreated = posOfObjs[text.size()];
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
	obj->setMesh(NULL);
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
