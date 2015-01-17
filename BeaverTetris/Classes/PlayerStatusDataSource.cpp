#include "PlayerStatusDataSource.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "CurrentPlayerDataSource.h"
#include "StringsSupporter.h"

using namespace std;

PlayerStatusDataSource::PlayerStatusDataSource(void)
{
	_currentPlayerDataSource = (CurrentPlayerDataSource*)ServiceLocator::getServiceForKey(currentPlayerDataSourceKey);
}


PlayerStatusDataSource::~PlayerStatusDataSource(void)
{
}

string PlayerStatusDataSource::getPlayerName()
{
	return _currentPlayerDataSource->getPlayerName();
}

string PlayerStatusDataSource::getPlayerScore()
{
	int score = _currentPlayerDataSource->getPlayerScore();
	string playerScore = StringsSupporter::getStringFromNumber(score);
	return playerScore;
}