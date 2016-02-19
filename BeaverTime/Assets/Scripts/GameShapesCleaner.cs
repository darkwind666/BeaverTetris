using UnityEngine;
using System.Collections.Generic;
using System;
using DG.Tweening;

public class GameShapesCleaner : MonoBehaviour {

    GameBoard _mainGameBoard;

    public GameObject animationTimeContainer;
    float _moveTimeForOneBlock;
    GameShapesSeparator _gameShapesSeparator;
    ShapeFinalPositionHelper _shapeFinalPositionHelper;

    void Start () {
        _moveTimeForOneBlock = animationTimeContainer.GetComponent<GameBoardCleaner>().moveTimeForOneBlock;
        _mainGameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _gameShapesSeparator = new GameShapesSeparator();
        _shapeFinalPositionHelper = new ShapeFinalPositionHelper();
    }
	
	void Update () {

        if (_mainGameBoard.gameBoardLocked == false)
        {
            List<List<GameObject>> blockShapes = _gameShapesSeparator.getBlockShapesOnGameBoard();
            downShapes(blockShapes);
        }

    }

    void downShapes(List<List<GameObject>> aShapes)
    {

        bool moveShapesDown = false;
        int maxDelta = 0;

        List<int> shapesDeltas = new List<int>();

        foreach (List<GameObject> shape in aShapes)
        {
            int yDelta = _shapeFinalPositionHelper.getYDeltaForShape(shape);

            if (yDelta > 0)
            {
                moveShapesDown = true;
                downShapeOnYDelta(shape, yDelta);
                maxDelta = Math.Max(maxDelta, yDelta);
            }

            shapesDeltas.Add(yDelta);
        }

        if (moveShapesDown)
        {
            _mainGameBoard.gameBoardLocked = true;
            Sequence explosionSequence = DOTween.Sequence();
            explosionSequence.AppendCallback(() => showShapesFollenAnimationWithDeltas(aShapes, shapesDeltas));
            explosionSequence.AppendInterval(maxDelta * _moveTimeForOneBlock);
            explosionSequence.AppendCallback(() => _mainGameBoard.gameBoardLocked = false);
        }

    }


    void downShapeOnYDelta(List<GameObject> aShape, int aDelta)
    {
        foreach (GameObject block in aShape)
        {
            int xPosition = (int)Mathf.Round(block.transform.localPosition.x);
            int yPosition = (int)Mathf.Round(block.transform.localPosition.y);
            GameObject blockInBoard = _mainGameBoard.getObjectForXY(xPosition, yPosition);

            if (block == blockInBoard)
            {
                _mainGameBoard.deleteObjectForXY(xPosition, yPosition);
            }

            int newYPosition = yPosition - aDelta;
            GameObject blockInBoardOnNextPosition = _mainGameBoard.getObjectForXY(xPosition, newYPosition);
            if (blockInBoardOnNextPosition)
            {
                _mainGameBoard.deleteObjectForXY(xPosition, newYPosition);
            }

            _mainGameBoard.setObjectForXY(block, xPosition, newYPosition);
        }
    }

    void showShapesFollenAnimationWithDeltas(List<List<GameObject>> aShapes, List<int> aShapesDeltas)
    {
        foreach (List<GameObject> shape in aShapes)
        {
            int objectIndex = aShapes.IndexOf(shape);
            int yDelta = aShapesDeltas[objectIndex];

            if (yDelta > 0)
            {
                foreach (GameObject block in shape)
                {
                    int xPosition = (int)Mathf.Round(block.transform.localPosition.x);
                    int yPosition = (int)Mathf.Round(block.transform.localPosition.y);
                    Vector3 newPosition = new Vector3(xPosition, yPosition - yDelta, block.transform.localPosition.z);
                    block.transform.DOLocalMove(newPosition, yDelta * _moveTimeForOneBlock);
                }
            }
        }
    }

}
