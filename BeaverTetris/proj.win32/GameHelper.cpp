#include "GameHelper.h"
#include "stdlib.h"
#include <ctime>

GameHelper::GameHelper(void)
{
}


GameHelper::~GameHelper(void)
{
}

int GameHelper::getRandomNumberFromUpInterval(int aUpInterval)
{
	srand(time(0));
	int randomNumber = rand() % aUpInterval;
	return randomNumber;
}