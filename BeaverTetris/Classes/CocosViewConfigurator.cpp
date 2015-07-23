#include "CocosViewConfigurator.h"
#include "CCPlatformConfig.h"
#include "GameViewConstants.h"

using namespace std;
using namespace cocos2d;

CocosViewConfigurator::CocosViewConfigurator(void)
{
	_standartResolutionOperationSystems = getStandartResolutionOperationSystems();
}

CocosViewConfigurator::~CocosViewConfigurator(void)
{
}

void CocosViewConfigurator::configurateView(GLView *aView)
{
	Size aScreenSize = aView->getFrameSize();
	setScalingAndResourcesFolderForScreenSize(aScreenSize);
}

vector<int> CocosViewConfigurator::getStandartResolutionOperationSystems()
{
	vector<int> standartResolutionOperationSystems;
	standartResolutionOperationSystems.push_back(CC_PLATFORM_WIN32);
	standartResolutionOperationSystems.push_back(CC_PLATFORM_LINUX);
	standartResolutionOperationSystems.push_back(CC_PLATFORM_MAC);
	standartResolutionOperationSystems.push_back(CC_PLATFORM_ANDROID);
	return standartResolutionOperationSystems;
}

void CocosViewConfigurator::configurateScreenSize(cocos2d::GLView *aView)
{
	vector<int>::iterator operationSystemsIterator;
	operationSystemsIterator = find(_standartResolutionOperationSystems.begin(), _standartResolutionOperationSystems.end(),CC_TARGET_PLATFORM);
	if (operationSystemsIterator != _standartResolutionOperationSystems.end())
	{
		aView->setFrameSize(designResolutionWidth, designResolutionHeight);
	}
}

void CocosViewConfigurator::setScalingAndResourcesFolderForScreenSize(Size aScreenSize)
{
	FileUtils *fileUtils = FileUtils::getInstance();
	Director *director = Director::getInstance();
	
	float mediumWidth = 640;
	float largeWidth = 1280;

	if (aScreenSize.width > mediumWidth)
	{
		fileUtils->addSearchPath(twoHighResolutionFolder);
		director->setContentScaleFactor(largeWidth / designResolutionWidth);
	}
	
	else if (aScreenSize.width > designResolutionWidth)
	{
		fileUtils->addSearchPath(highResolutionFolder);
		director->setContentScaleFactor(mediumWidth / designResolutionWidth);
	}
	
	else 
	{
		fileUtils->addSearchPath(standardResolutionFolder);
	}
}