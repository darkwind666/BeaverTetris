#pragma once

#include <string>
#include <vector>

class GameSoundDataSource
{
public:
	GameSoundDataSource(void);
	~GameSoundDataSource(void);

	int getEffectsCount();
	std::string getEffectForIndex(int aIndex);

	int getBackgroundSoundsCount();
	std::string getBackgroundSoundForIndex(int aIndex);

private:

	std::vector<std::string> _backgroundSounds;
	std::vector<std::string> _effects;

	std::vector<std::string> getBackgroundSounds();
	std::vector<std::string> getEffects();

};