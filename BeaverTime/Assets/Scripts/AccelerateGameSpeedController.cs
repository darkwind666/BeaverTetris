using UnityEngine;
using System.Collections;

public class AccelerateGameSpeedController : MonoBehaviour {

    public int eventType;
    int maxUpdateTime;
    int acceleratedSpeed;

    int _standardShapeSpeed;
    int _currentUpdateState;
    GameBoard _gameBoard;

    public GameObject gameSpeedContainer;
    GameSpeedController _gameSpeedController;

    public GameObject shapesContainer;
    GameShapesSpawner _shapeController;

    int activeDuration;
    bool _activeAcceleration;
    int _currentActiveAccelerationState;

    bool _eventActive;

    void Start () {

        _currentUpdateState = 0;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _gameSpeedController = gameSpeedContainer.GetComponent<GameSpeedController>();
        _shapeController = shapesContainer.GetComponent<GameShapesSpawner>();
        _standardShapeSpeed = _gameSpeedController.standardUpdateTime;
        _activeAcceleration = false;
        _currentActiveAccelerationState = 0;
        _eventActive = false;
        setAccelerateEventSettings();

    }

    void setAccelerateEventSettings()
    {
        LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelData.getCurrentLevelData();

        foreach (GameEvent gameEvent in level.levelEvents)
        {
            if (gameEvent.gameEventType == eventType)
            {
                maxUpdateTime = gameEvent.eventInterval;
                acceleratedSpeed = gameEvent.fallingSpeed;
                activeDuration = gameEvent.eventDuration;
                _eventActive = true;
                break;
            }
        }
    }

    void Update()
    {

    }

    public void updateWithGameTime()
    {
        if (_gameBoard.gameBoardLocked == false && _shapeController.currentShapeAvailable() && _eventActive == true)
        {
            updateAccelerateNegativeMoment();
        }
    }

    void updateAccelerateNegativeMoment()
    {
        if (_activeAcceleration)
        {
            updateActiveAcceleration();
        }
        else
        {
            updateInactiveAcceleration();
        }
    }

    void updateActiveAcceleration()
    {
        _currentActiveAccelerationState++;
        if (_currentActiveAccelerationState >= activeDuration)
        {
            stopAcceleration();
        }
    }

    void stopAcceleration()
    {
        if (_gameSpeedController.getCurrentGameSpeed() == acceleratedSpeed)
        {
            _gameSpeedController.setStandardShapeSpeed(_standardShapeSpeed);
            _gameSpeedController.stopShapeAcceleration();
        }
        else
        {
            _gameSpeedController.setStandardShapeSpeed(_standardShapeSpeed);
        }

        _currentActiveAccelerationState = 0;
        _activeAcceleration = false;
    }

    void updateInactiveAcceleration()
    {
        _currentUpdateState++;
        if (_currentUpdateState >= maxUpdateTime)
        {
            _currentUpdateState = 0;
            _gameSpeedController.setStandardShapeSpeed(acceleratedSpeed);
            _gameSpeedController.stopShapeAcceleration();
            _activeAcceleration = true;
        }
    }

}
