#pragma once
#include"../include/SFML/Audio.hpp"
#include "../game/Enums.hpp"
class AudioManager
{
private:

	sf::SoundBuffer _buffer[9];
	std::string _nameOfSound[9];
	std::string _path;
	sf::Music* _backgroundMusiclevel;
	sf::Music* _backgroundMusicMenu;
	sf::Sound _sound;
	bool _levelIsPlaying = false;
	bool _menuIsPlaying = false;
	AudioManager();

	static AudioManager* _audioManager;
public:

	static AudioManager* get();
	void PlaySound(SFX soundEnum);
	void LoadAllSFX();
	void GetNamesInString();
	void startLevelMusic();
	void startMenuMusic();
	~AudioManager();
};

