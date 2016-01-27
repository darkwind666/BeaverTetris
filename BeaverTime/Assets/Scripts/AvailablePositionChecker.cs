using UnityEngine;
using System.Collections;

public class AvailablePositionChecker {

    int _boardHeight;
    int _boardWidth;
    int _shapeSideInBlocks;

    public AvailablePositionChecker()
    {
        GameBoard gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _boardHeight = gameBoard.getBoardHeight();
        _boardWidth = gameBoard.getBoardWidth();
        _shapeSideInBlocks = gameBoard.getShapeSideInBlocks();
    }

    public bool checkAvailableObjectPosition(GameObject aObject, Vector3 aPosition)
    {
        bool available = true;
        bool childrenInBoard = checkShapeChildrenInBoard(aObject, aPosition);

        if (childrenInBoard == false)
        {
            available = false;
        }

        return available;

    }

    bool checkShapeChildrenInBoard(GameObject aShape, Vector3 aPosition)
    {
        GameBoard gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        bool available = true;

        foreach (Transform child in aShape.transform)
        {
            Vector3 childPositionOnBoard = child.localPosition + aPosition;
            
            if (gameBoard.checkPositionInBoard(childPositionOnBoard))
            {
               
                if(childPositionOnBoard.y < gameBoard.getBoardHeight())
                {
                    if (gameBoard.getObjectForXY((int)childPositionOnBoard.x, (int)childPositionOnBoard.y))
                    {
                        available = false;
                        break;
                    }
                }
                
                
            }
            else
            {
                available = false;
                break;
            }
        
        }

        return available;
    }

}
