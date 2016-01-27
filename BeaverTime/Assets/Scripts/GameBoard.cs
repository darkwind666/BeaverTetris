using UnityEngine;
using System.Collections;

public class GameBoard {

    GameObject[,] _gameBoard = new GameObject[20, 10];
    int _boardHeight;
    int _boardWidth;

    float _blockWidth;
    float _blockHeight;
    int _shapeSideInBlocks;

    public GameBoard(int aShapeSideInBlocks) {

        _shapeSideInBlocks = aShapeSideInBlocks;
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
                _gameBoard[yIndex, xIndex] = null;
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

    public int getShapeSideInBlocks()
    {
        return _shapeSideInBlocks;
    }

    public void setObjectForXY(GameObject aObject, int aXIndex, int aYIndex)
    {
        if(_gameBoard[aYIndex, aXIndex])
        {
            Object.Destroy(_gameBoard[aYIndex, aXIndex]);
        }
        _gameBoard[aYIndex, aXIndex] = aObject;
    }

    public GameObject getObjectForXY(int aXIndex, int aYIndex)
    {
        return _gameBoard[aYIndex, aXIndex];
    }

    public bool checkPositionInBoard(Vector3 aPosition)
    {
        bool available = true;

        bool availableWidth = ((aPosition.x >= 0) && (aPosition.x <= (_boardWidth - 1)));
        bool availableHeight = (aPosition.y >= 0);

        if (availableWidth == false || availableHeight == false)
        {
            available = false;
        }
        return available;
    }

    public void deleteObjectForXY(int aXIndex, int aYIndex)
    {
        _gameBoard[aYIndex, aXIndex] = null;
    }

}
