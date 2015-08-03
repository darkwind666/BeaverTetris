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
	
	float mediumHeight = 960;
	float largeHeight = 1920;

	GLint m_maxTextureSize = 0;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_maxTextureSize);

	if (aScreenSize.height > mediumHeight)
	{

		if (m_maxTextureSize == 8192)
		{
			fileUtils->addSearchPath(twoHighResolutionFolder);
			director->setContentScaleFactor(largeHeight / designResolutionHeight);
		}

		else if (m_maxTextureSize == 4096)
		{
			fileUtils->addSearchPath(highResolutionFolder);
			director->setContentScaleFactor(mediumHeight / designResolutionHeight);
		}

		else
		{
			fileUtils->addSearchPath(standardResolutionFolder);
		}
		
	}
	
	else if ( (aScreenSize.height > designResolutionHeight) && (m_maxTextureSize >= 4096) )
	{
		fileUtils->addSearchPath(highResolutionFolder);
		director->setContentScaleFactor(mediumHeight / designResolutionHeight);
	}
	
	else 
	{
		fileUtils->addSearchPath(standardResolutionFolder);
	}

}