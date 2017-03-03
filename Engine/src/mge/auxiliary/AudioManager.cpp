#include "AudioManager.h"
#include <iostream>
#include "../config.hpp"
using namespace sf;
using namespace std;

AudioManager* AudioManager::_audioManager;
AudioManager::AudioManager()
{
	_backgroundMusic = new Music();

	_path = config::MGE_SOUND_PATH;
	if (!_backgroundMusic->openFromFile(_path + "backgroundMusic1.wav")) {
		cout << "Couldn't load sound from file" << endl;
	}
	else {
		cout << " Playing background music" << endl;
		_backgroundMusic->openFromFile(_path + "backgroundMusic1.wav");
		_backgroundMusic->play();
	}
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

	for (int i = 0; i < 4; i++) {
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
	_nameOfSound[1] = "backButton1";
	_nameOfSound[2] = "enterButton1";
	_nameOfSound[3] = "switchButton1";
	
}

AudioManager::~AudioManager()
{
	delete _backgroundMusic;
}



