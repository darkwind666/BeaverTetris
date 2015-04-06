#include "SpellsViewDataSource.h"
#include "GameFileExtensionMaker.h"
#include "GameViewConstants.h"
#include "StringsSupporter.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "GameViewElementsKeys.h"
#include "GameKeyWithSuffixSupporter.h"
#include "GameElementsDataHelper.h"
#include "SpellBox.h"

using namespace std;
using namespace cocos2d;

SpellsViewDataSource::SpellsViewDataSource()
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
	_spellBox = (SpellBox*)ServiceLocator::getServiceForKey(spellBoxKey);
	_availableSpellsCount = _currentPlayerDataSource->getPlayerAvailableSpellsCount();
	_spellsInformation = makeSpellsInformation();
	_spellOffset = GameElementsDataHelper::getElementOffsetForKey(playerSpellsControllerKey);
}


SpellsViewDataSource::~SpellsViewDataSource(void)
{
}

vector<PlayerControllInformation> SpellsViewDataSource::makeSpellsInformation()
{
	vector<PlayerControllInformation> spellsInformation;

	PlayerControllInformation removeCurrentDetail;
	removeCurrentDetail.imageKey = removeCurrentDetailSpellKey;
	removeCurrentDetail.keyboardKey = (int)EventKeyboard::KeyCode::KEY_1;
	spellsInformation.push_back(removeCurrentDetail);

	PlayerControllInformation removeRandomTetraminos;
	removeRandomTetraminos.imageKey = removeRandomTetraminosSpellKey;
	removeRandomTetraminos.keyboardKey = (int)EventKeyboard::KeyCode::KEY_2;
	spellsInformation.push_back(removeRandomTetraminos);

	PlayerControllInformation firestormSpell;
	firestormSpell.imageKey = firestormSpellKey;
	firestormSpell.keyboardKey = (int)EventKeyboard::KeyCode::KEY_3;
	spellsInformation.push_back(firestormSpell);

	PlayerControllInformation cohesionSpell;
	cohesionSpell.imageKey = cohesionSpellKey;
	cohesionSpell.keyboardKey = (int)EventKeyboard::KeyCode::KEY_4;
	spellsInformation.push_back(cohesionSpell);

	return spellsInformation;
}

int SpellsViewDataSource::getAvailableSpellsCount()
{
	return _availableSpellsCount;
}

string SpellsViewDataSource::getSpellIconImageOnIndex(int aIndex)
{
	string spellKey = _spellsInformation[aIndex].imageKey;
	string spellImage = GameFileExtensionMaker::getGraphicWithExtension(spellKey);
	return spellImage;
}

string SpellsViewDataSource::getSpellRechargedIconImageOnIndex(int aIndex)
{
	string spellKey = _spellsInformation[aIndex].imageKey;
	string rechargedImage = GameKeyWithSuffixSupporter::makeRechargedImageForKey(spellKey);
	string spellImage = GameFileExtensionMaker::getGraphicWithExtension(rechargedImage);
	return spellImage;
}

float SpellsViewDataSource::getSpellRechargePercenOnIndex(int aIndex)
{
	PlayerControllInformation spell = _spellsInformation[aIndex];
	float rechargePercent = _spellBox->getSpellRechargePercentForKey(spell.imageKey);
	return rechargePercent;
}

bool SpellsViewDataSource::spellAvailableForIndex(int aIndex)
{
	PlayerControllInformation spell = _spellsInformation[aIndex];
	string spellKey = spell.imageKey;
	int spellCost = _spellBox->getSpellCostForKey(spellKey);
	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();

	bool spellAvailable = _spellBox->spellAvailableForKey(spellKey);
	bool enoughMoney = currentPlayerScore >= spellCost;
	return (enoughMoney == true && spellAvailable == true);
}

Vec2 SpellsViewDataSource::getSpellPositionOnIndex(int aIndex)
{
	return Vec2(0, - (aIndex * _spellOffset.y));
}

string SpellsViewDataSource::getSpellCostOnIndex(int aIndex)
{
	PlayerControllInformation spell = _spellsInformation[aIndex];
	int cost = _spellBox->getSpellCostForKey(spell.imageKey);
	string stringCost = StringsSupporter::getStringFromNumber(cost);
	return stringCost;
}

void SpellsViewDataSource::useSpellOnIndex(int aIndex)
{
	PlayerControllInformation spell = _spellsInformation[aIndex];
	string spellKey = spell.imageKey;
	int spellCost = _spellBox->getSpellCostForKey(spellKey);
	int currentPlayerScore = _currentPlayerDataSource->getPlayerScore();
	if (spellAvailableForIndex(aIndex))
	{
		_currentPlayerDataSource->setPlayerScore(currentPlayerScore - spellCost);
		_spellBox->useSpellForKey(spellKey);
	}
}

int  SpellsViewDataSource::getPlayerSpellKeyboardKeyOnIndex(int aIndex)
{
	PlayerControllInformation spell = _spellsInformation[aIndex];
	return spell.keyboardKey;
}