using UnityEngine;
using System.Collections.Generic;
using System;

public class WinBossCondition : MonoBehaviour, IWinCondition {

    public GameObject gameBoardPad;
    public GameObject[] bosses;
    public GameObject bossEnvironmentContainer;
    GameBoard _gameBoard;

    public List<GameObject> currentBosses;

    void Start () {

    }

    public void loadGameBoss()
    {
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        int bossType = getBossType();
        saveBossesWithType(bossType);
        placeAllBlocksFromPad(bossEnvironmentContainer);
        placeAllBlocksFromPad(bosses[bossType]);
    }

    void saveBossesWithType(int aBossType)
    {
		LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
		GameLevel level = levelData.getCurrentLevelData();
		int bossLivesCount = level.bossLivesCount;

        foreach (Transform child in bosses[aBossType].transform)
        {
			BlockLiveController liveController = child.GetComponent<BlockLiveController>();
			liveController.blockLivesCount = bossLivesCount;
            currentBosses.Add(child.gameObject);
        }
    }

    int getBossType()
    {
        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();
        return level.bossType;
    }

    void placeAllBlocksFromPad(GameObject aPad)
    {
        List<GameObject> children = new List<GameObject>();

        foreach (Transform child in aPad.transform)
        {
            children.Add(child.gameObject);
        }

        foreach (GameObject block in children)
        {
            setBlockInGameBoard(block);
        }
    }

    void setBlockInGameBoard(GameObject aBlock)
    {
        Vector3 childPositionOnBoard = aBlock.transform.localPosition;
        int positionX = (int)Mathf.Round(childPositionOnBoard.x);
        int positionY = (int)Mathf.Round(childPositionOnBoard.y);

        GameObject blockInBoard = _gameBoard.getObjectForXY(positionX, positionY);

        if (blockInBoard)
        {
            Destroy(blockInBoard);
        }

        aBlock.SetActive(true);
        _gameBoard.setObjectForXY(aBlock, positionX, positionY);
        aBlock.transform.SetParent(gameBoardPad.transform, false);
    }

    void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        foreach(GameObject boss in currentBosses)
        {
            if(boss)
            {
                win = false;
                break;
            }
        }

        return win;
    }

}
