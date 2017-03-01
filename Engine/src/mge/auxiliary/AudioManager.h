#pragma once
#include<SFML/Audio.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class AudioManager
{
private:

	SoundBuffer _buffer;

	Music* _backgroundMusic;
	Sound _sound;
public:
	AudioManager();
	void PlaySound();
	~AudioManager();
};

