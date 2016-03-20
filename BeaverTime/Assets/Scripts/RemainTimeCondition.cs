using UnityEngine;
using System.Collections;
using System;

public class RemainTimeCondition : MonoBehaviour, IWinCondition {

    int remainTime;
    int _currentTimeState;

    void Start () {

        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();
        remainTime = level.remainTimes;

        _currentTimeState = 0;

    }
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        _currentTimeState++;
        if(_currentTimeState < remainTime)
        {
            win = false;
        }

        return win;
    }

}
