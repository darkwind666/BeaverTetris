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
	configurateScreenSize(aView);
	Size aScreenSize = aView->getFrameSize();
	setScalingAndResourcesFolderForScreenSize(aScreenSize);
}

vector<int> CocosViewConfigurator::getStandartResolutionOperationSystems()
{
	vector<int> standartResolutionOperationSystems;
	standartResolutionOperationSystems.push_back(CC_PLATFORM_WIN32);
	standartResolutionOperationSystems.push_back(CC_PLATFORM_LINUX);
	standartResolutionOperationSystems.push_back(CC_PLATFORM_MAC);
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
	
	if (aScreenSize.height <= designResolutionHeight)
	{
		fileUtils->addSearchPath(standardResolutionFolder);
		director->setContentScaleFactor( aScreenSize.height / designResolutionHeight);
	}
	
	else if (aScreenSize.height > designResolutionHeight && aScreenSize.height <= designResolutionHeight * 2)
	{
		fileUtils->addSearchPath(highResolutionFolder);
		director->setContentScaleFactor(aScreenSize.height / designResolutionHeight * 2);
	}
	
	else if (aScreenSize.height > designResolutionHeight * 2 && aScreenSize.height <= designResolutionHeight * 4)
	{
		fileUtils->addSearchPath(twoHighResolutionFolder);
		director->setContentScaleFactor(aScreenSize.height / designResolutionHeight * 4);
	}
}