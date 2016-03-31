using UnityEngine;
using System.Collections;

public class PlayerInputController : MonoBehaviour {

    public GameShapesSpawner shapesController;
    public SpellsController spellsController;
    public GameSpeedController gameSpeedController;
    public string buttonCode { get; set; }

    ShapesLocator _shapesLocator;
    GameBoard _gameBoard;
    AvailablePositionChecker _positionChecker;

    const string moveRight = "MoveShapeRight";
    const string moveLeft = "MoveShapeLeft";
    const string accelerate = "AccelerateShape";
    const string rotate = "RotateShape";
    const string spell1 = "RemoveShape";
    const string spell2 = "RemoveRandomBlocks";
    const string spell3 = "FirestormSpell";
    const string spell4 = "CohessionSpell";

    void Start () {

        _shapesLocator = new ShapesLocator();
        _positionChecker = new AvailablePositionChecker();
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
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
        if (shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false)
        {
            checkUserInput();
        }
    }


    void checkUserInput()
    {
        if (Input.GetButtonDown(moveRight) || buttonCode == moveRight)
        {
            moveShapeRight();
        }
        else if (Input.GetButtonDown(moveLeft) || buttonCode == moveLeft)
        {
            moveShapeLeft();
        }
        else if (Input.GetButtonDown(accelerate) || buttonCode == accelerate)
        {
            acceleratedShapeSpeed();
        }
        else if (Input.GetButtonDown(rotate) || buttonCode == rotate)
        {
            rotateShape();
        }
        else if (Input.GetButtonDown(spell1) || buttonCode == spell1)
        {
            spellsController.removeCurrentShapeSpell();
        }
        else if (Input.GetButtonDown(spell2) || buttonCode == spell2)
        {
            spellsController.removeRandomBlocksSpell();
        }
        else if (Input.GetButtonDown(spell3) || buttonCode == spell3)
        {
            spellsController.firestormSpell();
        }
        else if (Input.GetButtonDown(spell4) || buttonCode == spell4)
        {
            spellsController.cohessionSpell();
        }

        buttonCode = "";
    }

    public void moveShapeRight()
    {
        GameObject currentShape = shapesController.currentShape();
        Vector3 currentPosition = currentShape.transform.localPosition;
        Vector3 direction = new Vector3(1, 0, 0);
        Vector3 newShapePosition = roundPosition(currentPosition + direction);
        tryChangeShapePosition(currentShape, newShapePosition);
    }

    public void moveShapeLeft()
    {
        GameObject currentShape = shapesController.currentShape();
        Vector3 currentPosition = currentShape.transform.localPosition;
        Vector3 direction = new Vector3(-1, 0, 0);
        Vector3 newShapePosition = roundPosition(currentPosition + direction);
        tryChangeShapePosition(currentShape, newShapePosition);
    }

    public void acceleratedShapeSpeed()
    {
        gameSpeedController.setAcceleratedShapeSpeed();
    }

    public void rotateShape()
    {
        GameObject currentShape = shapesController.currentShape();
        Vector3 point = new Vector3(1, 1, 0);
        Vector3 rotatePoint = currentShape.transform.TransformPoint(point);
        rotateCurrentShapeAroundPoint(rotatePoint);
    }

    void rotateCurrentShapeAroundPoint(Vector3 rotatePoint)
    {
        GameObject currentShape = shapesController.currentShape();
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

    public void downShape()
    {
        if (shapesController.currentShapeAvailable())
        {
            GameObject currentShape = shapesController.currentShape();
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
                shapesController.createNewShape();
                gameSpeedController.stopShapeAcceleration();
            }

        }
    }

}
