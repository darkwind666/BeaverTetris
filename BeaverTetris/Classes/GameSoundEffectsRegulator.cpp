#include "GameSoundEffectsRegulator.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameSoundController.h"
#include "GameSoundsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameViewElementsKeys.h"
#include "CocosNodesHelper.h"

using namespace cocos2d;
using namespace ui;
using namespace experimental;

GameSoundEffectsRegulator::GameSoundEffectsRegulator(void)
{

	CocosNodesHelper::addSpriteToParentNodeWithKey(this, startGameRegulateSoundPlaceKey);
	CocosNodesHelper::addSpriteToParentNodeWithKey(this, startGameRegulateSoundEffectsIconKey);

	Slider *soundEffectsRegulator = Slider::create();
	string loadBarTextureName = GameFileExtensionMaker::getGraphicWithExtension(startGameRegulateSoundProgressKey);
	string loadBarThumbTextureName = GameFileExtensionMaker::getGraphicWithExtension(startGameRegulateSoundThumbKey);
	soundEffectsRegulator->loadBarTexture(loadBarTextureName, TextureResType::PLIST);
	soundEffectsRegulator->loadSlidBallTextureNormal(loadBarThumbTextureName, TextureResType::PLIST);
	soundEffectsRegulator->loadSlidBallTexturePressed(loadBarThumbTextureName, TextureResType::PLIST);

	float percent = getRegulatorPercent();
	soundEffectsRegulator->setPercent(percent);
	function<void(Ref*,Widget::TouchEventType)> eventListner = getEventListnerForRegulator();
	soundEffectsRegulator->addTouchEventListener(eventListner);
	this->addChild(soundEffectsRegulator);
	
}


GameSoundEffectsRegulator::~GameSoundEffectsRegulator(void)
{
}

int GameSoundEffectsRegulator::getRegulatorPercent()
{
	GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
	float percent = gameSoundController->getCurrentSoundEffectsVolume();
	int percentForRegulator = percent * 100;
	return percentForRegulator;
}

function<void(Ref*, Widget::TouchEventType)> GameSoundEffectsRegulator::getEventListnerForRegulator()
{
	function<void(Ref*,Widget::TouchEventType)> eventListner = [](Ref *sender, Widget::TouchEventType aType){
		if (aType == Widget::TouchEventType::ENDED)
		{
			Slider *sendedSlider = (Slider*)sender;
			int percent = sendedSlider->getPercent();
			float volume = percent / 100.0f;
			GameSoundController *gameSoundController = (GameSoundController*)ServiceLocator::getServiceForKey(gameSoundControllerKey);
			gameSoundController->setCurrentSoundEffectsVolume(volume);
			string volumeCheckSound = GameFileExtensionMaker::getSoundWithExtension(buttonPressedSoundKey);
			gameSoundController->playSoundEffectForKey(volumeCheckSound);
		}
	};
	return eventListner;
}