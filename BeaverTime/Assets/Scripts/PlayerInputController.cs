using UnityEngine;
using System.Collections;

public class PlayerInputController : MonoBehaviour {

    public int standardUpdateTime;
    public int acceleratedUpdateTime;
    int _maxUpdateTime;
    int _currentUpdateState;
    public GameObject shapesContainer;
    GameShapesSpawner _shapesController;
    ShapesLocator _shapesLocator;

    AvailablePositionChecker _positionChecker;


    void Start () {

        _shapesLocator = new ShapesLocator();
        _positionChecker = new AvailablePositionChecker();
        GameBoard gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _shapesController = shapesContainer.GetComponent<GameShapesSpawner>();
        _maxUpdateTime = standardUpdateTime;
        _currentUpdateState = 0;

    }

    Vector3 roundPosition(Vector3 aPosition)
    {
        return new Vector3(Mathf.Round(aPosition.x), Mathf.Round(aPosition.y), Mathf.Round(aPosition.z));
    }

    void tryChangeShapePosition(GameObject aShape, Vector3 aPosition)
    {
        if(_positionChecker.checkAvailableObjectPosition(aShape, aPosition))
        {
            aShape.transform.localPosition = aPosition;
        }
    }

    void Update()
    {
        checkUserInput();
        _currentUpdateState++;
        if(_currentUpdateState >= _maxUpdateTime)
        {
            _currentUpdateState = 0;
            downShape();
        }
    }


    void checkUserInput()
    {
        
        GameObject currentShape = _shapesController.currentShape();
        Vector3 currentPosition = currentShape.transform.localPosition;

        if (Input.GetKeyDown(KeyCode.RightArrow))
        {
            Vector3 direction = new Vector3(1, 0, 0);
            Vector3 newShapePosition = roundPosition(currentPosition + direction);
            tryChangeShapePosition(currentShape, newShapePosition);
        }
        else if (Input.GetKeyDown(KeyCode.LeftArrow))
        {
            Vector3 direction = new Vector3( -1, 0, 0);
            Vector3 newShapePosition = roundPosition(currentPosition + direction);
            tryChangeShapePosition(currentShape, newShapePosition);
        }
        if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            _maxUpdateTime = acceleratedUpdateTime;
        }
        else if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            Vector3 point = new Vector3(1, 1, 0);
            Vector3 rotatePoint = currentShape.transform.TransformPoint(point);

            foreach (Transform child in currentShape.transform)
            {
                child.RotateAround(rotatePoint, Vector3.forward, 90);
                child.localPosition = roundPosition(child.localPosition);
            }

            
            if (_positionChecker.checkAvailableObjectPosition(currentShape, currentShape.transform.localPosition) == false)
            {
                foreach (Transform child in currentShape.transform)
                {
                    child.RotateAround(rotatePoint, Vector3.forward, -90);
                    child.localPosition = roundPosition(child.localPosition);
                }
            }
            
        }
        
    }

    void downShape()
    {
        if (_shapesController.currentShapeAvailable())
        {
            GameObject currentShape = _shapesController.currentShape();
            Vector3 currentPosition = currentShape.transform.localPosition;

            Vector3 direction = new Vector3(0, -1, 0);
            Vector3 newShapePosition = roundPosition(currentPosition + direction);

            if (_positionChecker.checkAvailableObjectPosition(currentShape, newShapePosition))
            {
                currentShape.transform.localPosition = newShapePosition;
            }
            else
            {
                _shapesLocator.writeShapeInBoard(currentShape);
                _shapesController.createNewShape();
                _maxUpdateTime = standardUpdateTime;
            }

        }
    }

}
