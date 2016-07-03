using UnityEngine;
using System.Collections.Generic;

public class RemoveBlocksCondition : MonoBehaviour, IWinCondition {

    public Dictionary<int, int> removeBlocksToWin;

	void Start () {

        removeBlocksToWin = new Dictionary<int, int>();

        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();

        foreach (BlocksForRemoving blockData in level.blocks)
        {
            removeBlocksToWin.Add(blockData.blockType, blockData.blocksCount);
        }

    }
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        foreach(KeyValuePair<int, int> pair in removeBlocksToWin)
        {
            if(pair.Value > 0)
            {
                win = false;
                break;
            }
        }

        return win;
    }

    public void blockWasRemoovedWithType(int aBlockType)
    {
        if(removeBlocksToWin != null)
        {
            if (removeBlocksToWin.ContainsKey(aBlockType))
            {
                removeBlocksToWin[aBlockType] = removeBlocksToWin[aBlockType] - 1;
                if(removeBlocksToWin[aBlockType] < 0)
                {
                    removeBlocksToWin[aBlockType] = 0;
                }
            }
        }
    }

}
