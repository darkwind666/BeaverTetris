using UnityEngine;
using System.Collections;

public class WinConditionPadController : MonoBehaviour {

    GameObject[] winConditionsIndicators;
    GameObject[] winBlocksIndicators;
    GameObject[] winBossesIndicators;

    void Start () {

        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel levelData = levelDataStore.getCurrentLevelData();

        GameObject levelIndicator = winConditionsIndicators[levelData.winConditionType];
        levelIndicator.SetActive(true);

    }
	
	void Update () {
	
	}
}
