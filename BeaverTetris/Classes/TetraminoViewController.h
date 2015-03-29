#pragma once

#include "cocos2d.h"
#include <string>

class TetraminoColorsDataSource;

class TetraminoViewController : public cocos2d::Node
{
public:
	TetraminoViewController(void);
	TetraminoViewController(std::string aTexture, std::string aLivesCount);
	~TetraminoViewController(void);

	virtual void setOpacity(GLubyte opacity);

	void setTexture(std::string aTexture);
	void setLivesCount(std::string aLivesCount);
	std::string getTextureName();
	std::string getLivesCount();

private:

	cocos2d::Sprite *_tetraminoTexture;
	cocos2d::LabelTTF *_tetraminoLives;
	TetraminoColorsDataSource *_tetraminoColorsDataSource;

};

