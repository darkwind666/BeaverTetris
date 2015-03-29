#include "TetraminoViewController.h"
#include "CocosNodesHelper.h"
#include "GameViewElementsKeys.h"
#include "GameViewStyleHelper.h"
#include "TetraminoColorsDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"

using namespace std;
using namespace cocos2d;

TetraminoViewController::TetraminoViewController(void)
{
	Sprite *tetraminoTexture = Sprite::create("HelloWorld.png");
	tetraminoTexture->setScaleX(0.05f);
	tetraminoTexture->setScaleY(0.08f);
	tetraminoTexture->setName("");
	_tetraminoTexture = tetraminoTexture;
	this->addChild(tetraminoTexture);

	LabelTTF *tetraminoLives = GameViewStyleHelper::getStandardLabel();
	tetraminoLives->setFontSize(20);
	_tetraminoLives = tetraminoLives;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(tetraminoLives, this, tetraminoLivesCountViewKey);

	_tetraminoColorsDataSource = (TetraminoColorsDataSource*)ServiceLocator::getServiceForKey(tetraminoColorsDataSourceKey);
}


TetraminoViewController::TetraminoViewController(string aTexture, string aLivesCount)
{
	Sprite *tetraminoTexture = Sprite::create("HelloWorld.png");
	tetraminoTexture->setScaleX(0.05f);
	tetraminoTexture->setScaleY(0.08f);
	Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(aTexture);
	tetraminoTexture->setColor(tetraminoColor);
	tetraminoTexture->setName(aTexture);
	_tetraminoTexture = tetraminoTexture;
	this->addChild(tetraminoTexture);
	
	LabelTTF *tetraminoLives = GameViewStyleHelper::getStandardLabel();
	tetraminoLives->setFontSize(20);
	tetraminoLives->setString(aLivesCount);
	_tetraminoLives = tetraminoLives;
	CocosNodesHelper::addChildNodeToParentNodeWithKey(tetraminoLives, this, tetraminoLivesCountViewKey);

	_tetraminoColorsDataSource = (TetraminoColorsDataSource*)ServiceLocator::getServiceForKey(tetraminoColorsDataSourceKey);
}

TetraminoViewController::~TetraminoViewController(void)
{
}

void TetraminoViewController::setTexture(string aTexture)
{
	Color3B tetraminoColor = _tetraminoColorsDataSource->getColorForKey(aTexture);
	_tetraminoTexture->setColor(tetraminoColor);
	_tetraminoTexture->setName(aTexture);
}

void TetraminoViewController::setLivesCount(string aLivesCount)
{
	_tetraminoLives->setString(aLivesCount);
}

string TetraminoViewController::getTextureName()
{
	string textureName = _tetraminoTexture->getName();
	return textureName;
}

string TetraminoViewController::getLivesCount()
{
	string livesCount = _tetraminoLives->getString();
	return livesCount;
}

void TetraminoViewController::setOpacity(GLubyte opacity)
{
	_tetraminoTexture->setOpacity(opacity);
	_tetraminoLives->setOpacity(opacity);
}