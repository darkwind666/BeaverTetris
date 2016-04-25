using UnityEngine;
using System.Collections.Generic;

public class ShapeFinalPositionHelper {

    GameBoard _mainGameBoard;

    public ShapeFinalPositionHelper()
    {
        _mainGameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
    }

    public int getYDeltaForShape(List<GameObject> aShape)
    {
        int yDelta = 0;

        while (availablePositionForShapeWithYDelta(aShape, yDelta + 1))
        {
            yDelta++;
        }

        return yDelta;
    }

    bool availablePositionForShapeWithYDelta(List<GameObject> aShape, int aDelta)
    {
        bool availablePosition = true;

        bool shapeInBoard = checkShapeBlocksPositionsInBoard(aShape, aDelta);
        if (shapeInBoard)
        {
            if (collideWithOtherShapes(aShape, aDelta))
            {
                availablePosition = false;
            }
        }
        else
        {
            availablePosition = false;
        }

        return availablePosition;
    }

    bool checkShapeBlocksPositionsInBoard(List<GameObject> aShape, int aDelta)
    {
        bool inBoard = true;

        foreach (GameObject block in aShape)
        {
            Vector3 blockPosition = block.transform.localPosition;
            Vector3 blockPositionWithDelta = new Vector3(blockPosition.x, blockPosition.y - aDelta, blockPosition.z);
            Vector3 newBlockPosition = new Vector3(Mathf.Round(blockPositionWithDelta.x), Mathf.Round(blockPositionWithDelta.y), blockPosition.z);

            if (_mainGameBoard.checkPositionInBoard(newBlockPosition) == false)
            {
                inBoard = false;
                break;
            }

        }

        return inBoard;
    }

    bool collideWithOtherShapes(List<GameObject> aShape, int aDelta)
    {
        bool collide = false;

        foreach (GameObject block in aShape)
        {
            Vector3 blockPosition = block.transform.localPosition;
            Vector3 blockPositionWithDelta = new Vector3(blockPosition.x, blockPosition.y - aDelta, blockPosition.z);
            int xPosition = (int)Mathf.Round(blockPositionWithDelta.x);
            int yPosition = (int)Mathf.Round(blockPositionWithDelta.y);

            if(yPosition < _mainGameBoard.getBoardHeight())
            {
                GameObject blockInBoard = _mainGameBoard.getObjectForXY(xPosition, yPosition);

                if (blockInBoard)
                {
                    if (aShape.Contains(blockInBoard) == false)
                    {
                        collide = true;
                        break;
                    }

                }
            }

        }

        return collide;
    }

}
