using UnityEngine;
using System.Collections.Generic;

public class GameBossesController : MonoBehaviour {

    public GameObject gameBoardPad;
    public GameObject[] bosses;
    public GameObject bossEnvironmentContainer;
    public int bossType;
    GameBoard _gameBoard;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        placeAllBlocksFromPad(bossEnvironmentContainer);
        placeAllBlocksFromPad(bosses[bossType]);

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

        _gameBoard.setObjectForXY(aBlock, positionX, positionY);
        aBlock.transform.SetParent(gameBoardPad.transform, false);
    }

    void Update () {
	
	}


}
