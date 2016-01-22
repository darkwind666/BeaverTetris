using UnityEngine;
using System.Collections;

public class GameBoard : MonoBehaviour {

    GameObject[,] _gameBoard = new GameObject[20, 10];
    int _boardHeight;
    int _boardWidth;

    void Start () {

        _boardHeight = _gameBoard.GetLength(0);
        _boardWidth = _gameBoard.GetLength(1);
        cleanGameBoard();

	}
	
    void cleanGameBoard()
    {

        for (int yIndex = 0; yIndex < _boardHeight; yIndex++)
        {
            for (int xIndex = 0; xIndex < _boardWidth; xIndex++)
            {
                _gameBoard[yIndex, xIndex] = new GameObject();
            }
        }

    }

    void Update () {
	
	}

    public int getBoardHeight()
    {
        return _boardHeight;
    }

    public int getBoardWidth()
    {
        return _boardWidth;     
    }

    public void setObjectForXY(GameObject aObject, int aXIndex, int aYIndex)
    {
        _gameBoard[aYIndex, aXIndex] = aObject;
    }

    public GameObject getObjectForXY(int aXIndex, int aYIndex)
    {
        return _gameBoard[aYIndex, aXIndex];
    }

}
