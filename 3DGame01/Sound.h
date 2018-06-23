#ifndef _SOUND_H
#define _SOUND_H
/*This is the sound class. This class can be used to play sounds. Still need to do more testing with it.*/
#include <SFML\Audio.hpp>
#include <iostream>
class Sound
{
public:
	Sound(char* path);
	void play();
	void pause();
	bool isPlaying();
	bool isPaused();
	~Sound();
private:
	char* _path;
	bool _isPlaying;
	bool _isPaused;
	sf::Sound _sound;
	sf::SoundBuffer _soundBuffer;
};


#endif