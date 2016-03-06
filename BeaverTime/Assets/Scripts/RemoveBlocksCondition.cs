using UnityEngine;
using System.Collections.Generic;

public class RemoveBlocksCondition : MonoBehaviour, IWinCondition {

    Dictionary<int, int> _removeBlocksToWin;

	void Start () {

        _removeBlocksToWin = new Dictionary<int, int>();

        _removeBlocksToWin.Add(1, 10);
        _removeBlocksToWin.Add(2, 20);

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
        if(_removeBlocksToWin.ContainsKey(aBlockType))
        {
            _removeBlocksToWin[aBlockType] = _removeBlocksToWin[aBlockType] - 1;
        }
    }

}
