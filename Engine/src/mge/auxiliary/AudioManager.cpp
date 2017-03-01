#include "AudioManager.h"
#include <iostream>
#include "../config.hpp"
using namespace sf;
using namespace std;

AudioManager* AudioManager::_audioManager;
//Constructor
AudioManager::AudioManager()
{
	//_backgroundMusic = new Music();
	//if (!_backgroundMusic->openFromFile("background.wav")) {
	//	cout << "Couldn't load sound from file" << endl;
	//}
	//else {
	//	_backgroundMusic->openFromFile("background.wav");
	//	_backgroundMusic->play();
	//}
	_path = config::MGE_SOUND_PATH;
	GetNamesInString();
	LoadAllSFX();
}

AudioManager* AudioManager::get() {
		if (!_audioManager)
			_audioManager = new AudioManager();

		return _audioManager;
}

//Used to play the shooting sound
void AudioManager::PlaySound(SFX soundEnum) {
	_sound.setBuffer(_buffer[soundEnum]);
	_sound.setLoop(false);
	if (_sound.getStatus() != sf::Sound::Playing)
	{
		_sound.play();
	}
}

void AudioManager::LoadAllSFX() {

	for (int i = 0; i < 2; i++) {
		if (!_buffer[i].loadFromFile(_path + _nameOfSound[i] + ".wav")) {
			cout << "Couldn't load SFX from file" << endl;

		}
		else {
			_buffer[i].loadFromFile(_path + _nameOfSound[i] + ".wav");
		}
	}
}

void AudioManager::GetNamesInString() {

	_nameOfSound[0] = "playerJump1";
	_nameOfSound[1] = "keySwitch";
	
}

AudioManager::~AudioManager()
{
	delete _backgroundMusic;
}



