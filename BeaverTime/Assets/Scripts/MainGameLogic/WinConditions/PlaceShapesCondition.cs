using UnityEngine;
using System.Collections;
using System;

public class PlaceShapesCondition : MonoBehaviour, IWinCondition {

    public GameShapesSpawner gameShapesSpawner;

    int winShapesCount;

    void Start () {

        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();
        winShapesCount = level.needToPlaceDetailsCount;
    }
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        if(gameShapesSpawner.getFallenShapesCount() <= winShapesCount)
        {
            win = false;
        }

        return win;
    }

}
