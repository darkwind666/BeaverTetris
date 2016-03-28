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

        GamePlayerDataController gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        if(spellType <  gamePlayerData.getPlayerSpellsCount())
        {
            LevelSpell spellData = gamePlayerData.getPlayerSpellForIndex(spellType);
            spellRechargeInterval = spellData.spellRechargeInterval;
            _playerHasSpell = true;
        }

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
        int spellCount = 0;

        GamePlayerDataController gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        if (spellType < gamePlayerData.getPlayerSpellsCount())
        {
            LevelSpell spellData = gamePlayerData.getPlayerSpellForIndex(spellType);
            spellCount = spellData.spellCount;
        }

        return spellCount;
    }

}
