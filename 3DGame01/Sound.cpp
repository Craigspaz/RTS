#include "Sound.h"


Sound::Sound(char* path)
	:
	_path(path),
	_isPlaying(false),
	_isPaused(false)
{
	if (!_soundBuffer.loadFromFile(_path))
	{
		std::cout << "Can't find file\n";
	}
	else
	{
		std::cout << "Sound Loaded...\n";
	}
	_sound.setBuffer(_soundBuffer);
}



Sound::~Sound()
{
}


void Sound::play()
{
	_sound.play();
	_isPlaying = true;
	std::cout << "Playing...\n";
	if (_sound.getStatus() == _sound.Stopped)
	{
		_isPlaying = false;
	}
}
void Sound::pause()
{
	_sound.pause();
	_isPaused = true;
	std::cout << "Paused...\n";
}
bool Sound::isPlaying()
{
	return _isPlaying;
}
bool Sound::isPaused()
{
	return _isPaused;
}
