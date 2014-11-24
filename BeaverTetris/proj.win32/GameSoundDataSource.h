#pragma once

#include <string>

class GameSoundDataSource
{
public:
	GameSoundDataSource(void);
	~GameSoundDataSource(void);

	int getSoundsCount();
	std::string getSoundForIndex(int aIndex);

private:

	std::string *_sounds;
	int _soundsElementsCount;

};