using UnityEngine;
using System.Collections;
using System;

public class PlaceShapesCondition : MonoBehaviour, IWinCondition {

    public GameObject shapesSpawnerContainer;
    GameShapesSpawner _gameShapesSpawner;

    int winShapesCount;

    void Start () {

        _gameShapesSpawner = shapesSpawnerContainer.GetComponent<GameShapesSpawner>();

        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();
        winShapesCount = level.needToPlaceDetailsCount;
    }
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        if(_gameShapesSpawner.getFallenShapesCount() <= winShapesCount)
        {
            win = false;
        }

        return win;
    }

}
