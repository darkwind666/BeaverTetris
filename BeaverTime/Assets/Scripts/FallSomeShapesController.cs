using UnityEngine;
using System.Collections.Generic;
using DG.Tweening;

public class FallSomeShapesController : MonoBehaviour {

    public int maxUpdateTime;
    public int fallShapesCount;
    public float fallSpeed;
    public GameObject gameBoardPad;
    int _currentUpdateState;
    GameBoard _gameBoard;

    public GameObject shapesContainer;
    GameShapesSpawner _shapeController;
    ShapeFinalPositionHelper _shapeFinalPositionHelper;

    void Start() {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _currentUpdateState = 0;
        _shapeController = shapesContainer.GetComponent<GameShapesSpawner>();
        _shapeFinalPositionHelper = new ShapeFinalPositionHelper();

    }

    void Update() {

    }

    public void updateWithGameTime()
    {
        if (_gameBoard.gameBoardLocked == false && _shapeController.currentShapeAvailable())
        {
            _currentUpdateState++;
            if (_currentUpdateState >= maxUpdateTime)
            {
                _currentUpdateState = 0;
                fallSomeShapes();
            }
        }
    }

    void fallSomeShapes()
    {
        List<GameObject> shapes = getShapesForFallen();
        fallShapes(shapes);
    }

    List<GameObject> getShapesForFallen()
    {
        List<GameObject> shapes = new List<GameObject>();

        for (int shapeIndex = 0; shapeIndex < fallShapesCount; shapeIndex++)
        {
            int randomXPosition = getRandomShapePosition();
            Vector3 shapeStartPosition = new Vector3(randomXPosition, 21, 0);

            GameObject shape = _shapeController.createStandardShape();
            shape.transform.localPosition = shapeStartPosition;
            shapes.Add(shape);
        }

        return shapes;
    }

    int getRandomShapePosition()
    {
        int randomShapeXPosition;
        List<int> availablePositions = getAvailablePositions();

        int randomNamber = Random.Range(0, availablePositions.Count);
        randomShapeXPosition = availablePositions[randomNamber];

        return randomShapeXPosition;
    }

    List<int>  getAvailablePositions()
    {
        int shapeXPosition = Mathf.RoundToInt(_shapeController.currentShape().transform.localPosition.x);
        int maxUpInterval = shapeXPosition - 3;
        int maxDownInterval = shapeXPosition + 3;

        List<int> availablePositions = new List<int>();

        for (int xIndex = 0; xIndex <= (_gameBoard.getBoardWidth() - 3); xIndex++)
        {
            if (xIndex <= maxUpInterval || xIndex >= maxDownInterval)
            {
                availablePositions.Add(xIndex);
            }
        }

        return availablePositions;
    }


    void fallShapes(List<GameObject> aShapes)
    {
        _gameBoard.gameBoardLocked = true;
        Sequence fallShapesSequence = DOTween.Sequence();

        foreach (GameObject shape in aShapes)
        {
            Vector3 finalShapePosition = getFinalShapePosition(shape);
            writeShapeInBoardOnPosition(shape, finalShapePosition);

            float moveDuration = Mathf.Abs(shape.transform.localPosition.y - finalShapePosition.y);
            float shapeMoveDuration = moveDuration * fallSpeed / 60;

            fallShapesSequence.Append(shape.transform.DOLocalMove(finalShapePosition, shapeMoveDuration));
            GameObject gameShape = shape;
            fallShapesSequence.AppendCallback(()=> placeShapesBlocksOnGamePadOnPosition(gameShape, finalShapePosition));
            fallShapesSequence.AppendCallback(() => Destroy(gameShape));
        }

        fallShapesSequence.AppendCallback(() => _gameBoard.gameBoardLocked = false);
    }

    Vector3 getFinalShapePosition(GameObject aShape)
    {
        List<GameObject> blocks = new List<GameObject>();

        foreach(Transform blockTransform in aShape.transform)
        {
            blockTransform.localPosition = blockTransform.localPosition + aShape.transform.localPosition;
            blocks.Add(blockTransform.gameObject);
        }

        int yDelta = _shapeFinalPositionHelper.getYDeltaForShape(blocks);
        int yPosition = (int)aShape.transform.localPosition.y - yDelta;

        foreach (Transform blockTransform in aShape.transform)
        {
            blockTransform.localPosition = blockTransform.localPosition - aShape.transform.localPosition;
        }

        return new Vector3(aShape.transform.localPosition.x, yPosition, aShape.transform.localPosition.z);
    }

    void writeShapeInBoardOnPosition(GameObject aShape, Vector3 aPosition)
    {
        foreach (Transform child in aShape.transform)
        {
            Vector3 childPositionOnBoard = child.transform.localPosition + aPosition;
            int positionX = (int)Mathf.Round(childPositionOnBoard.x);
            int positionY = (int)Mathf.Round(childPositionOnBoard.y);

            if(positionY < _gameBoard.getBoardHeight())
            {
                _gameBoard.setObjectForXY(child.gameObject, positionX, positionY);
            }
            
        }
    }

    void placeShapesBlocksOnGamePadOnPosition(GameObject aShape, Vector3 aPosition)
    {
        List<GameObject> children = new List<GameObject>();

        foreach (Transform child in aShape.transform)
        {
            children.Add(child.gameObject);
        }

        foreach (GameObject childObject in children)
        {
            childObject.transform.localPosition = childObject.transform.localPosition + aShape.transform.localPosition;
            if(childObject.transform.localPosition.y < _gameBoard.getBoardHeight())
            {
                childObject.transform.SetParent(gameBoardPad.transform, false);
            }
            
        }

    }

}
