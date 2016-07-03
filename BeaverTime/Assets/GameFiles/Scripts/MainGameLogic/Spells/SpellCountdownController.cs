using UnityEngine;
using System.Collections;

public class SpellCountdownController : MonoBehaviour {

    public int spellType;
    public int spellScorePrice;

    public int spellRechargeInterval;
    public int spellRechargeState;
    bool _playerHasSpell;

	void Start () {

        _playerHasSpell = false;

		checkEndlessLevel();
		checkPlayerSpellsCount();

        spellRechargeState = spellRechargeInterval;
    }
	
	void Update () {
	
	}

    public void updateWithGameTime()
    {
        if (spellRechargeState <= spellRechargeInterval)
        {
            spellRechargeState++;
        }
    }

    public void useSpell()
    {
        spellRechargeState = 0;
    }

    public bool availableSpell()
    {
        return ((spellRechargeState >= spellRechargeInterval) && _playerHasSpell);
    }

    public int getSpellCount()
    {
		LevelSpell spellData = getCurrentLevelSpellData();
		return spellData.spellCount;
    }

	void checkEndlessLevel()
	{
		GamePlayerDataController gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		if(gamePlayerData.selectEndlessLevel)
		{
			LevelSpell spellData = getCurrentLevelSpellData();
			spellRechargeInterval = spellData.spellRechargeInterval;
			_playerHasSpell = true;
		}
	}

	void checkPlayerSpellsCount()
	{
		GamePlayerDataController gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		if(spellType <  gamePlayerData.getPlayerSpellsCount())
		{
			LevelSpell spellData = getCurrentLevelSpellData();
			spellRechargeInterval = spellData.spellRechargeInterval;
			_playerHasSpell = true;
		}
	}

	LevelSpell getCurrentLevelSpellData()
	{
		LevelSpell spellData = new LevelSpell();
		GamePlayerDataController gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

		if (gamePlayerData.selectEndlessLevel) {
			LevelDataStore currentLevelData = ServicesLocator.getServiceForKey (typeof(LevelDataStore).Name) as LevelDataStore;
			spellData = currentLevelData.getCurrentLevelData ().levelSpells [spellType];
		} else {
			
			if(spellType <  gamePlayerData.getPlayerSpellsCount())
			{
				spellData = gamePlayerData.getPlayerSpellForIndex(spellType);
			}

		}

		return spellData;
	}

}
