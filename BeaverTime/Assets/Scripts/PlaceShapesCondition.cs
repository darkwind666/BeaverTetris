using UnityEngine;
using System.Collections;
using System;

public class PlaceShapesCondition : MonoBehaviour, IWinCondition {

    public GameObject shapesSpawnerContainer;
    GameShapesSpawner _gameShapesSpawner;

    public int winShapesCount;

    void Start () {

        _gameShapesSpawner = shapesSpawnerContainer.GetComponent<GameShapesSpawner>();

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
