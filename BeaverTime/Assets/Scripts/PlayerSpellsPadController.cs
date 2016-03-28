using UnityEngine;
using System.Collections;

public class PlayerSpellsPadController : MonoBehaviour {

    public GameObject[] playerSpells;
    GamePlayerDataController _gamePlayerData;

    void Start () {

        _gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        for (int spellIndicatorIndex = 0; spellIndicatorIndex < _gamePlayerData.getPlayerSpellsCount(); spellIndicatorIndex++)
        {
            GameObject spellIndicator = playerSpells[spellIndicatorIndex];
            spellIndicator.SetActive(true);
        }
        
    }
	
	void Update () {
	
	}
}
