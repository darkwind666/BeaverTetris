#include "CurrentLevelWinResultDataSource.h"

CurrentLevelWinResultDataSource::CurrentLevelWinResultDataSource(void)
{
}


CurrentLevelWinResultDataSource::~CurrentLevelWinResultDataSource(void)
{
}

bool CurrentLevelWinResultDataSource::winGameResult()
{
	return true;
}

bool CurrentLevelWinResultDataSource::winAllGameResult()
{
	return true;
}

bool CurrentLevelWinResultDataSource::winCurrentGame(void)
{
	return true;
}

std::string CurrentLevelWinResultDataSource::getCurrentLevelName()
{
	return std::string("sasha");
}

int CurrentLevelWinResultDataSource::getCurrentLevelAward()
{
	return 42;
}

void CurrentLevelWinResultDataSource::setCurrentGameWinResult(bool winResult)
{

}