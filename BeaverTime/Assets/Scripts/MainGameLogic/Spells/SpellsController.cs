using UnityEngine;
using System.Collections.Generic;
using System;

public class SpellsController : MonoBehaviour {

    public GameObject[] spells;
    public GameAnaliticsController gameAnaliticsController;
    GamePlayerDataController _gamePlayerData;

    void Start ()
    {
        _gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
    }

    void Update () {

	}

    public void updateWithGameTime()
    {
        foreach(GameObject spellContainer in spells)
        {
            SpellCountdownController sepllCountdown = spellContainer.GetComponent<SpellCountdownController>();
            sepllCountdown.updateWithGameTime();
        }
    }

    public void removeCurrentShapeSpell()
    {

        useSpellForIndex(0);
    }

    public void removeRandomBlocksSpell()
    {
        useSpellForIndex(1);
    }

    public void firestormSpell()
    {
        useSpellForIndex(2);
    }

    public void cohessionSpell()
    {
        useSpellForIndex(3);
    }

    void useSpellForIndex(int aSpellIndex)
    {
		if (aSpellIndex < _gamePlayerData.getPlayerSpellsCount() || _gamePlayerData.selectEndlessLevel == true)
        {
            GameObject spellContainer = spells[aSpellIndex];
            useSpellFromSpellContainer(spellContainer);
        }
    }

    void useSpellFromSpellContainer(GameObject aSpellContainer)
    {
        SpellCountdownController spellCountdown = aSpellContainer.GetComponent<SpellCountdownController>();
        if (spellCountdown.availableSpell() && _gamePlayerData.playerScore >= spellCountdown.spellScorePrice)
        {
            ISpell spell = aSpellContainer.GetComponent<ISpell>();

            if (spell.availableSpell())
            {
                spell.useSpell();
                spellCountdown.useSpell();
                _gamePlayerData.playerScore = _gamePlayerData.playerScore - spellCountdown.spellScorePrice;
                gameAnaliticsController.sendUseSpellMessage(spellCountdown.spellType + 1);
            }

        }
    }

}
