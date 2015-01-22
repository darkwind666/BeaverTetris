#include "KeysForEnumsDataSource.h"
#include "GameViewElementsKeys.h"

using namespace std;

KeysForEnumsDataSource::KeysForEnumsDataSource(void)
{
	_tetraminoKeys = makeTetraminoKeys();
}


KeysForEnumsDataSource::~KeysForEnumsDataSource(void)
{
}

map<TetraminoType, string> KeysForEnumsDataSource::makeTetraminoKeys()
{
	
	map<TetraminoType, string> tetraminoKeys;

	tetraminoKeys[kTetraminoRed] = redTetraminoKey;
	tetraminoKeys[kTetraminoGreen] = greenTetraminoKey;
	tetraminoKeys[kTetraminoBlue] = blueTetraminoKey;
	tetraminoKeys[kTetraminoGold] = goldTetraminoKey;
	tetraminoKeys[kTetraminoBlack] = blackTetraminoKey;
	tetraminoKeys[kTetraminoBossQueen] = queenTetraminoKey;
	tetraminoKeys[kTetraminoBossPrincess] = princessTetraminoKey;
	tetraminoKeys[kTetraminoBossKing] = kingTetraminoKey;

	return tetraminoKeys;
}

string KeysForEnumsDataSource::getKeyForTetraminoType(TetraminoType aTetraminoType)
{
	return _tetraminoKeys[aTetraminoType];
}
