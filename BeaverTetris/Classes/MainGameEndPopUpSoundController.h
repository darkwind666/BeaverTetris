#pragma once

#include <string>

class WinGameSystem;
class CurrentLevelDataSource;

class MainGameEndPopUpSoundController
{
public:
	MainGameEndPopUpSoundController(void);
	~MainGameEndPopUpSoundController(void);

	void playEndGameSound();
	void stopPlayingSound();

private:

	WinGameSystem *_winGameSystem;
	CurrentLevelDataSource *_currentLevelDataSource;

	void playGameResultSound();
	void playWinGameSound();
	void playSoundWithKey(std::string aKey);

};

