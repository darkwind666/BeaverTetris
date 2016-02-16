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
    GameBoard _gameBoard;

    AvailablePositionChecker _positionChecker;

    public GameObject spellsContainer;
    SpellsController _spellsController;


    void Start () {

        _shapesLocator = new ShapesLocator();
        _positionChecker = new AvailablePositionChecker();
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _shapesController = shapesContainer.GetComponent<GameShapesSpawner>();
        _maxUpdateTime = standardUpdateTime;
        _currentUpdateState = 0;
        _spellsController = spellsContainer.GetComponent<SpellsController>();

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

        if (_shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false)
        {
            checkUserInput();
        }

        _currentUpdateState++;
        if(_currentUpdateState >= _maxUpdateTime && _gameBoard.gameBoardLocked == false)
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
        else if (Input.GetKeyDown(KeyCode.DownArrow))
        {
            _maxUpdateTime = acceleratedUpdateTime;
        }
        else if (Input.GetKeyDown(KeyCode.UpArrow))
        {
            Vector3 point = new Vector3(1, 1, 0);
            Vector3 rotatePoint = currentShape.transform.TransformPoint(point);
            rotateCurrentShapeAroundPoint(rotatePoint);
        }
        else if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            _spellsController.removeCurrentShapeSpell();
        }
        else if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            _spellsController.removeRandomBlocksSpell();
        }
        else if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            _spellsController.firestormSpell();
        }
        else if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            _spellsController.cohessionSpell();
        }

    }

    void rotateCurrentShapeAroundPoint(Vector3 rotatePoint)
    {
        GameObject currentShape = _shapesController.currentShape();
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

    public void setStandardShapeSpeed()
    {
        _maxUpdateTime = standardUpdateTime;
    }

}
