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

	public int minActiveDuration;
	public int minUpdateTimeForEvent;
	public int minAcceleratedSpeed;
	public int endlessLevelWaveTimeInterval;
	int _maxActiveDuration;
	int _maxUpdateTimeForEvent;
	int _maxAcceleratedSpeed;

	int _currentWaveTimeState;

    void Start () {

        currentUpdateState = 0;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
		_playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        _standardShapeSpeed = gameSpeedController.standardUpdateTime;
        activeAcceleration = false;
        _currentActiveAccelerationState = 0;
        _eventActive = false;

        setAccelerateEventSettings();

		_maxActiveDuration = activeDuration;
		_maxUpdateTimeForEvent = maxUpdateTime;
		_maxAcceleratedSpeed = acceleratedSpeed;

		if (_playerData.selectEndlessLevel) {

			maxUpdateTime = minUpdateTimeForEvent;
			acceleratedSpeed = minAcceleratedSpeed;
			activeDuration = minActiveDuration;
			_currentWaveTimeState = 0;
			_eventActive = true;
		}

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

		if (_playerData.selectEndlessLevel) 
		{
			updateEndlessLevelWave();
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

	void updateEndlessLevelWave()
	{
		_currentWaveTimeState++;

		if(_currentWaveTimeState >= endlessLevelWaveTimeInterval)
		{
			_currentWaveTimeState = 0;

			maxUpdateTime = Mathf.Min(maxUpdateTime - 10, minUpdateTimeForEvent);
			if (maxUpdateTime <= _maxUpdateTimeForEvent) {
				maxUpdateTime = minUpdateTimeForEvent;
			}

			activeDuration = Mathf.Min(activeDuration + 10, _maxActiveDuration);
			if (activeDuration >= _maxActiveDuration) {
				activeDuration = minActiveDuration;
			}

			acceleratedSpeed = Mathf.Max(acceleratedSpeed - 2, _maxAcceleratedSpeed);
			if (acceleratedSpeed <= _maxAcceleratedSpeed) {
				acceleratedSpeed = minAcceleratedSpeed;
			}
		}
	}

	public void breakNegativeMomentWithReward(int aReward)
	{
		_playerData.playerScore = _playerData.playerScore + aReward;
		makeNegativeMoment();
	}

}
