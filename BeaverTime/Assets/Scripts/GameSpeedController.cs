using UnityEngine;
using System.Collections;

public class GameSpeedController : MonoBehaviour {

    public int standardUpdateTime;
    public int acceleratedUpdateTime;
    int _maxUpdateTime;
    int _currentUpdateState;

    GameBoard _gameBoard;

    public GameObject shapesContainer;
    GameShapesSpawner _shapesController;

    public GameObject playerInputContainer;
    PlayerInputController _playerInputController;

    void Start () {

        _maxUpdateTime = standardUpdateTime;
        _currentUpdateState = 0;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _shapesController = shapesContainer.GetComponent<GameShapesSpawner>();
        _playerInputController = playerInputContainer.GetComponent<PlayerInputController>();

    }
	
	void Update () {

        if (_shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false)
        {
            _currentUpdateState++;

            if (_currentUpdateState >= _maxUpdateTime)
            {
                _currentUpdateState = 0;
                _playerInputController.downShape();
            }

        }

    }

    public void setAcceleratedShapeSpeed()
    {
        _maxUpdateTime = acceleratedUpdateTime;
    }

    public void setStandardShapeSpeed()
    {
        _maxUpdateTime = standardUpdateTime;
    }

}
