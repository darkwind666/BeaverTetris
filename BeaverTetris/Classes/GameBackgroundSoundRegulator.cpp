#include "GameBackgroundSoundRegulator.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameFileExtensionMaker.h"
#include "GameViewElementsKeys.h"
#include "CocosNodesHelper.h"

using namespace cocos2d;
using namespace ui;
using namespace experimental;

GameBackgroundSoundRegulator::GameBackgroundSoundRegulator(void)
{
	Slider *backgroundSoundRegulator = Slider::create();

	string loadBarTextureName = GameFileExtensionMaker::getGraphicWithExtension(startGameRegulateSoundPlaceKey);
	string loadBarThumbTextureName = GameFileExtensionMaker::getGraphicWithExtension(startGameRegulateSoundThumbKey);
	backgroundSoundRegulator->loadBarTexture(loadBarTextureName, TextureResType::PLIST);
	backgroundSoundRegulator->loadSlidBallTextureNormal(loadBarThumbTextureName, TextureResType::PLIST);
	backgroundSoundRegulator->loadSlidBallTexturePressed(loadBarThumbTextureName, TextureResType::PLIST);

	float percent = getRegulatorPercent();
	backgroundSoundRegulator->setPercent(percent);
	function<void(Ref*,Widget::TouchEventType)> eventListner = getEventListnerForRegulator();
	backgroundSoundRegulator->addTouchEventListener(eventListner);
	this->addChild(backgroundSoundRegulator);
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, startGameRegulateBackgroundSoundIconKey);

}


GameBackgroundSoundRegulator::~GameBackgroundSoundRegulator(void)
{
}

int GameBackgroundSoundRegulator::getRegulatorPercent()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	float percent = gameSoundController->getCurrentBackgroundSoundVolume();
	int percentForRegulator = percent * 100;
	return percentForRegulator;
}

function<void(Ref*, Widget::TouchEventType)> GameBackgroundSoundRegulator::getEventListnerForRegulator()
{
	function<void(Ref*,Widget::TouchEventType)> eventListner = [](Ref *sender, Widget::TouchEventType aType){
		if (aType == Widget::TouchEventType::ENDED)
		{
			Slider *sendedSlider = (Slider*)sender;
			int percent = sendedSlider->getPercent();
			float volume = percent / 100.0f;
			GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
			gameSoundController->setCurrentBackgroundSoundVolume(volume);
		}
	};
	return eventListner;
}