using UnityEngine;
using System.Collections;
using System;

public class RemainTimeCondition : MonoBehaviour, IWinCondition {

    public int remainTime;
    public int currentTimeState;

    void Start () {

        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();
        remainTime = level.remainTimes;

        currentTimeState = 0;

    }
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        currentTimeState++;
        if(currentTimeState < remainTime)
        {
            win = false;
        }

        return win;
    }

}
