#include "GameHelper.h"
#include "stdlib.h"

GameHelper::GameHelper(void)
{
}


GameHelper::~GameHelper(void)
{
}

int GameHelper::getRandomNumberFromUpInterval(int aUpInterval)
{
	int randomNumber = rand() % aUpInterval;
	return randomNumber;
}
