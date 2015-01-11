#include "GameGraphicsLoader.h"
#include "GameGraphicsDataSource.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

GameGraphicsLoader::GameGraphicsLoader()
{
	_gameGraphicsDataSource = new GameGraphicsDataSource();
}


GameGraphicsLoader::~GameGraphicsLoader(void)
{
}

void GameGraphicsLoader::setInitialGraphic()
{
	string initialGraphic = _gameGraphicsDataSource->getInitialGraphic();
	string initialGraphicFrame = _gameGraphicsDataSource->getInitialGraphicFrame();
	setGraphicWithFrameAndFile(initialGraphicFrame, initialGraphic);
}

int GameGraphicsLoader::getGraphicCount()
{
	return _gameGraphicsDataSource->getGraphicCount();
}

void GameGraphicsLoader::loadGraphicForIndex(int aIndex)
{
	string graphic = _gameGraphicsDataSource->getInitialGraphic();
	string graphicFrame = _gameGraphicsDataSource->getInitialGraphicFrame();
	setGraphicWithFrameAndFile(graphicFrame, graphic);
}

void GameGraphicsLoader::setGraphicWithFrameAndFile(string frame, string file)
{
	TextureCache *textureCache = CCDirector::getInstance()->getTextureCache();
	textureCache->addImage(file);
	
	SpriteFrameCache *spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile(frame);
}