using UnityEngine;
using System.Collections;

public class GameSpeedController : MonoBehaviour {

    public int standardUpdateTime;
    public int acceleratedUpdateTime;
    int _maxUpdateTime;
    int _currentUpdateState;
    int _currentStandardUpdateTime;

    GameBoard _gameBoard;

    public GameObject shapesContainer;
    GameShapesSpawner _shapesController;

    public GameObject playerInputContainer;
    PlayerInputController _playerInputController;

    public GameObject fallSomeShapesContainer;
    FallSomeShapesController _fallSomeShapesController;

    public GameObject accelerateGameSpeedContainer;
    AccelerateGameSpeedController _accelerateGameSpeedController;

    void Start () {

        _maxUpdateTime = standardUpdateTime;
        _currentStandardUpdateTime = standardUpdateTime;
        _currentUpdateState = 0;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _shapesController = shapesContainer.GetComponent<GameShapesSpawner>();
        _playerInputController = playerInputContainer.GetComponent<PlayerInputController>();
        _fallSomeShapesController = fallSomeShapesContainer.GetComponent<FallSomeShapesController>();
        _accelerateGameSpeedController = accelerateGameSpeedContainer.GetComponent<AccelerateGameSpeedController>();

    }
	
	void Update () {

        if (_shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false)
        {
            _currentUpdateState++;

            if (_currentUpdateState >= _maxUpdateTime)
            {
                _currentUpdateState = 0;
                _playerInputController.downShape();
                _accelerateGameSpeedController.updateWithGameTime();
                _fallSomeShapesController.updateWithGameTime();
            }

        }

    }

    public int getCurrentGameSpeed()
    {
        return _maxUpdateTime;
    }

    public void setAcceleratedShapeSpeed()
    {
        _maxUpdateTime = acceleratedUpdateTime;
    }

    public void stopShapeAcceleration()
    {
        _maxUpdateTime = _currentStandardUpdateTime;
    }

    public void setStandardShapeSpeed(int aSpeed)
    {
        _currentStandardUpdateTime = aSpeed;
    }

}
