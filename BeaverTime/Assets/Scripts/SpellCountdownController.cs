using UnityEngine;
using System.Collections;

public class SpellCountdownController : MonoBehaviour {

    public int spellType;
    public int spellScorePrice;

    int _spellRechargeInterval;
    int _spellRechargeState;
    bool _playerHasSpell;

	void Start () {

        _playerHasSpell = false;

        GamePlayerDataController gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        if(spellType <  gamePlayerData.getPlayerSpellsCount())
        {
            LevelSpell spellData = gamePlayerData.getPlayerSpellForIndex(spellType);
            _spellRechargeInterval = spellData.spellRechargeInterval;
            _playerHasSpell = true;
        }

        _spellRechargeState = _spellRechargeInterval;
    }
	
	void Update () {
	
	}

    public void updateWithGameTime()
    {
        if (_spellRechargeState <= _spellRechargeInterval)
        {
            _spellRechargeState++;
        }
    }

    public void useSpell()
    {
        _spellRechargeState = 0;
    }

    public bool availableSpell()
    {
        return ((_spellRechargeState >= _spellRechargeInterval) && _playerHasSpell);
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
