#include "StringsSupporter.h"
#include <sstream>

using namespace std;

StringsSupporter::StringsSupporter(void)
{
}


StringsSupporter::~StringsSupporter(void)
{
}

string StringsSupporter::getStringFromNumber(int aNumber)
{
	stringstream str;
	str << aNumber;
	string numberInString = str.str();
	return numberInString;
}