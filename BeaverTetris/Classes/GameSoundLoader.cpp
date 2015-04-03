#include "GameSoundLoader.h"
#include "cocos2d.h"
#include "AudioEngine.h"

using namespace std;
using namespace cocos2d;
using namespace experimental;

GameSoundLoader::GameSoundLoader(void)
{
}

GameSoundLoader::~GameSoundLoader(void)
{
}

void GameSoundLoader::loadResources()
{
	AudioEngine::lazyInit();
}


