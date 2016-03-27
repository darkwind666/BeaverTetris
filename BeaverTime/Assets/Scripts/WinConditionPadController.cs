using UnityEngine;
using System.Collections;

public class WinConditionPadController : MonoBehaviour {

    public GameObject[] winConditionsIndicators;
    public GameObject[] winBlocksIndicators;
    public GameObject[] winBossesIndicators;

    void Start () {

        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel levelData = levelDataStore.getCurrentLevelData();

        GameObject levelIndicator = winConditionsIndicators[levelData.winConditionType];
        levelIndicator.SetActive(true);

        checkWinBlocksLevel(levelData);
        checkWinBoss(levelData);

    }

    void checkWinBlocksLevel(GameLevel aLevelData)
    {
        if(aLevelData.winConditionType == 1)
        {
            GameObject indicator;
            if (aLevelData.blocks.Length == 2)
            {
               indicator = winBlocksIndicators[0];
            }
            else
            {
               indicator = winBlocksIndicators[1];
            }
            indicator.SetActive(true);
        }
    }

    void checkWinBoss(GameLevel aLevelData)
    {
        if (aLevelData.winConditionType == 3)
        {
            GameObject indicator = winBossesIndicators[aLevelData.bossType];
            indicator.SetActive(true);
        }
    }

    void Update () {
	
	}
}
