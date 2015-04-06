#pragma once

#include <string>
#include <map>
#include "GameStructures.h"

class CurrentPlayerSpellsDelegate
{
public:
	CurrentPlayerSpellsDelegate(void);
	~CurrentPlayerSpellsDelegate(void);

	void setNewPlayerSpells(std::map<std::string, LevelSpellInformation> aSpells);
	std::map<std::string, LevelSpellInformation> getPlayerSpells();
	void cleanPlayerSpells();

	int getSpellCountForKey(std::string aKey);
	int getSpellRechargeIntervalForKey(std::string aKey);

	void setNewSpellCountForKey(int spellCount, std::string aKey);
	void setNewSpellRechargeIntervalForKey(int spellRechargeInterval, std::string aKey);

private:

	std::map<std::string, LevelSpellInformation> _playerSpells;

	void setNewSpellInformationForKey(LevelSpellInformation aSpellInformation, std::string aKey);
	void setSpellInformationForKey(LevelSpellInformation aSpellInformation, std::string aKey);
	LevelSpellInformation getSpellInformationForKey(std::string aKey);

};

