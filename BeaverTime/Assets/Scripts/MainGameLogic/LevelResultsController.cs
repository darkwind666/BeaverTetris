using UnityEngine;
using System.Collections;

public class LevelResultsController : MonoBehaviour {

    public FadingScript fadingController;
    public GameSpeedController gameSpeedController;
    public GameObject resultPopUp;
    public GameLevelsCollection gameLevelsCollection;
    public GameObject[] results;
    public AudioSource winLevelSound;
    public AudioSource loseLevelSound;
    public AudioSource winGameSound;
    public MainGameSoundsController soundController;
    public GameAnaliticsController gameAnaliticsController;
	public int endlessLevelStartScore;

    GamePlayerDataController _playerData;
    GameLevel _currentLevelData;
    PlayersDatabaseController _playersRecords;

    const string escape = "Cancel";

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        _playersRecords = ServicesLocator.getServiceForKey(typeof(PlayersDatabaseController).Name) as PlayersDatabaseController;
        LevelDataStore levelsDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        _currentLevelData = levelsDataStore.getCurrentLevelData();
        _playerData.playerStartLevelScore = _playerData.playerScore;

		if (_playerData.selectEndlessLevel) 
		{
			_playerData.playerScore = endlessLevelStartScore;
		}

    }
	
	
	void Update () {

    }

    public void winLevel()
    {
        soundController.backgroundSound.Stop();
        gameSpeedController.stopGame = true;
        resultPopUp.SetActive(true);
        _playerData.playerScore = _playerData.playerScore + _currentLevelData.levelAward;
        _playerData.playerStartLevelScore = _playerData.playerScore;

        GameObject result = getPlayerResult();
        result.SetActive(true);

        gameAnaliticsController.sendWinlevelMessage();

        float volume = soundController.backgroundSound.volume;
        soundController.backgroundSound.volume = volume;
        soundController.backgroundSound.Play();
    }

    GameObject getPlayerResult()
    {
        GameObject result;
        if (_playerData.selectedLevelIndex >= (gameLevelsCollection.gameLevels.Length - 1))
        {
            result = results[2];

            PlayerRecordData newRecord = new PlayerRecordData(_playerData.playerName, _playerData.playerScore);
            _playersRecords.saveNewPlayerRecord(newRecord);
            _playerData.cleanPlayer();

            soundController.backgroundSound = winGameSound;
        }
        else
        {
            result = results[1];

            if (_playerData.selectedLevelIndex > (_playerData.completedLevelsCount - 1))
            {
                _playerData.completedLevelsCount = _playerData.completedLevelsCount + 1;
            }

            _playerData.savePlayerData();

            soundController.backgroundSound = winLevelSound;
        }

        return result;
    }

    public void loseLevel()
    {
        _playerData.playerScore = _playerData.playerStartLevelScore;
        _playerData.savePlayerData();
        gameSpeedController.stopGame = true;
        resultPopUp.SetActive(true);
        GameObject result = results[0];
        result.SetActive(true);

        gameAnaliticsController.sendLoselevelMessage();

        soundController.backgroundSound.Stop();
        float volume = soundController.backgroundSound.volume;
        soundController.backgroundSound = loseLevelSound;
        soundController.backgroundSound.volume = volume;
        soundController.backgroundSound.Play();

    }

    public void nextLevel()
    {
        _playerData.selectedLevelIndex = _playerData.selectedLevelIndex + 1;
        fadingController.startFade("MainGameScreen", false);
    }

    public void goToSelectLevelScreenFromPause()
    {
        _playerData.playerScore = _playerData.playerStartLevelScore;
        _playerData.savePlayerData();
        fadingController.startFade("SelectLevelScreen", false);
    }

}
