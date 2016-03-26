using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class RemoveBlocksController : MonoBehaviour {

    public GameObject[] bloksIndicators;
    public RemoveBlocksCondition removeBlocksCondition;

    GameLevel _levelData;

    void Start () {

        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        _levelData = levelData.getCurrentLevelData();

    }
	
	void Update () {

        for (int indicatorIndex = 0; indicatorIndex < bloksIndicators.Length; indicatorIndex++)
        {
            Text indicator = bloksIndicators[indicatorIndex].GetComponent<Text>();
            BlocksForRemoving block = _levelData.blocks[indicatorIndex];
            int indicatorValue = removeBlocksCondition.removeBlocksToWin[block.blockType];
            indicator.text = indicatorValue.ToString();
        }

	}

}
