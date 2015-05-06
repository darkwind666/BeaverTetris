#include "AppDelegate.h"
#include "CocosViewConfigurator.h"
#include "GameInitiator.h"
#include "GATrackerpp.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("BeaverTetris");
		CocosViewConfigurator *cocosViewConfigurator = new CocosViewConfigurator();
		cocosViewConfigurator->configurateView(glview);
		delete cocosViewConfigurator;
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	GameInitiator *gameInitiator = new GameInitiator();
	gameInitiator->setInitialState();
	delete gameInitiator;

	GATrackerpp analyticHelper("UA-61796273-1", "71798b3b-97af-433e-a83a-fc95f95e50f5");
	

	analyticHelper.sendAppView("MyDemoApp", "v2","Main screen7", true, false);

	for (int i = 0; i < 500000; i++)
	{
		CCLOG("Sasha");
	}

	analyticHelper.sendAppView("MyDemoApp", "v2","Main screen8", false, true);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
