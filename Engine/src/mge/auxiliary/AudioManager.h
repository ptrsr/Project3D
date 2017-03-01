#pragma once
#include"../include/SFML/Audio.hpp"
#include "../game/Enums.hpp"
class AudioManager
{
private:

	sf::SoundBuffer _buffer[2];
	std::string _nameOfSound[2];
	std::string _path;
	sf::Music* _backgroundMusic;
	sf::Sound _sound;
	AudioManager();

	static AudioManager* _audioManager;
public:

	static AudioManager* get();
	void PlaySound(SFX soundEnum);
	void LoadAllSFX();
	void GetNamesInString();
	~AudioManager();
};

