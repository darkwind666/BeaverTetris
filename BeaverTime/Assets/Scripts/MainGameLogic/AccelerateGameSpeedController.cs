using UnityEngine;
using System.Collections;

public class AccelerateGameSpeedController : MonoBehaviour {

    public int eventType;
	public int maxUpdateTime;
    int acceleratedSpeed;

    int _standardShapeSpeed;
	public int currentUpdateState;
    GameBoard _gameBoard;
	public int negativeMomentReward;

    public GameSpeedController gameSpeedController;
    public GameShapesSpawner shapeController;

    int activeDuration;
	public bool activeAcceleration;
    int _currentActiveAccelerationState;

    bool _eventActive;
	GamePlayerDataController _playerData;

    void Start () {

        currentUpdateState = 0;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
		_playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        _standardShapeSpeed = gameSpeedController.standardUpdateTime;
        activeAcceleration = false;
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
        if (_gameBoard.gameBoardLocked == false && shapeController.currentShapeAvailable() && _eventActive == true)
        {
            updateAccelerateNegativeMoment();
        }
    }

    void updateAccelerateNegativeMoment()
    {
        if (activeAcceleration)
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
        if (gameSpeedController.getCurrentGameSpeed() == acceleratedSpeed)
        {
            gameSpeedController.setStandardShapeSpeed(_standardShapeSpeed);
            gameSpeedController.stopShapeAcceleration();
        }
        else
        {
            gameSpeedController.setStandardShapeSpeed(_standardShapeSpeed);
        }

        _currentActiveAccelerationState = 0;
        activeAcceleration = false;
    }

    void updateInactiveAcceleration()
    {
        currentUpdateState++;
        if (currentUpdateState >= maxUpdateTime)
        {
			makeNegativeMoment();
        }
    }

	void makeNegativeMoment()
	{
		currentUpdateState = 0;
		gameSpeedController.setStandardShapeSpeed(acceleratedSpeed);
		gameSpeedController.stopShapeAcceleration();
		activeAcceleration = true;
	}

	public void breakNegativeMomentWithReward(int aReward)
	{
		_playerData.playerScore = _playerData.playerScore + aReward;
		makeNegativeMoment();
	}

}
