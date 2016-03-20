using UnityEngine;
using System.Collections.Generic;

public class RemoveBlocksCondition : MonoBehaviour, IWinCondition {

    Dictionary<int, int> _removeBlocksToWin;

	void Start () {

        _removeBlocksToWin = new Dictionary<int, int>();

        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();

        foreach (BlocksForRemoving blockData in level.blocks)
        {
            _removeBlocksToWin.Add(blockData.blockType, blockData.blocksCount);
        }

    }
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        foreach(KeyValuePair<int, int> pair in _removeBlocksToWin)
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
        if(_removeBlocksToWin != null)
        {
            if (_removeBlocksToWin.ContainsKey(aBlockType))
            {
                _removeBlocksToWin[aBlockType] = _removeBlocksToWin[aBlockType] - 1;
            }
        }
    }

}
