#pragma once

#include <vector>
#include "cocos2d.h"

class CocosViewConfigurator
{
public:
	CocosViewConfigurator(void);
	~CocosViewConfigurator(void);

	void configurateView(cocos2d::GLView *aView);

private:

	std::vector<int> _standartResolutionOperationSystems;

	std::vector<int> getStandartResolutionOperationSystems();
	void configurateScreenSize(cocos2d::GLView *aView);
	void setScalingAndResourcesFolderForScreenSize(cocos2d::Size aScreenSize);
};

