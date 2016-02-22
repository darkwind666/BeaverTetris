using UnityEngine;
using System.Collections.Generic;

public class GameBossesController : MonoBehaviour {

    public GameObject gameBoardPad;
    public GameObject bossEnvironmentContainer;
    GameBoard _gameBoard;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        createEnvironmentForBoss();
        createBoss();

    }

    void createEnvironmentForBoss()
    {

        List<GameObject> children = new List<GameObject>();

        foreach (Transform child in bossEnvironmentContainer.transform)
        {
            children.Add(child.gameObject);
        }

        foreach(GameObject block in children)
        {
            Vector3 childPositionOnBoard = block.transform.localPosition;
            int positionX = (int)Mathf.Round(childPositionOnBoard.x);
            int positionY = (int)Mathf.Round(childPositionOnBoard.y);
            _gameBoard.setObjectForXY(block, positionX, positionY);
            block.transform.SetParent(gameBoardPad.transform, false);
        }

    }

    void createBoss()
    {

    }

    void Update () {
	
	}


}
