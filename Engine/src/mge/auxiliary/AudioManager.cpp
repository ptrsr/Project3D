#include "stdafx.h"
#include "AudioManager.h"

//Constructor
AudioManager::AudioManager()
{
	_backgroundMusic = new Music();
	if (!_backgroundMusic->openFromFile("background.wav")) {
		cout << "Couldn't load sound from file" << endl;
	}
	else {
		_backgroundMusic->openFromFile("background.wav");
		_backgroundMusic->play();
	}
	if (!_buffer.loadFromFile("shooting.wav")) {
		cout << "Couldn't load sound from file" << endl;

	}
	else {
		_buffer.loadFromFile("shooting.wav");
	}
}

//Used to play the shooting sound
void AudioManager::PlaySound() {
	_sound.setBuffer(_buffer);
	_sound.setLoop(false);
	if (_sound.getStatus() != sf::Sound::Playing)
	{
		_sound.play();
	}
}



AudioManager::~AudioManager()
{
	delete _backgroundMusic;
}
