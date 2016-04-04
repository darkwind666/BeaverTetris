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

    GamePlayerDataController _playerData;
    GameLevel _currentLevelData;
    PlayersDatabaseController _playersRecords;

    int _playerStartScore;

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        _playersRecords = ServicesLocator.getServiceForKey(typeof(PlayersDatabaseController).Name) as PlayersDatabaseController;
        LevelDataStore levelsDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        _currentLevelData = levelsDataStore.getCurrentLevelData();
        _playerStartScore = _playerData.playerScore;

    }
	
	
	void Update () {
	
	}

    public void winLevel()
    {

        soundController.backgroundSound.Stop();
        float volume = soundController.backgroundSound.volume;

        gameSpeedController.stopGame = true;
        resultPopUp.SetActive(true);

        _playerData.playerScore = _playerData.playerScore + _currentLevelData.levelAward;

        GameObject result;
        if (_playerData.selectedLevelIndex >= (gameLevelsCollection.gameLevels.Length - 1))
        {
            result = results[2];
            soundController.backgroundSound = winGameSound;
        }
        else
        {
            result = results[1];

            if (_playerData.selectedLevelIndex > (_playerData.completedLevelsCount - 1))
            {
                _playerData.completedLevelsCount = _playerData.completedLevelsCount + 1;
            }
            soundController.backgroundSound = winLevelSound;
        }

        _playerData.savePlayerData();

        result.SetActive(true);

        soundController.backgroundSound.volume = volume;
        soundController.backgroundSound.Play();
    }

    public void loseLevel()
    {
        _playerData.playerScore = _playerStartScore;
        gameSpeedController.stopGame = true;
        resultPopUp.SetActive(true);
        GameObject result = results[0];
        result.SetActive(true);

        soundController.backgroundSound.Stop();
        float volume = soundController.backgroundSound.volume;
        soundController.backgroundSound = loseLevelSound;
        soundController.backgroundSound.volume = volume;
        soundController.backgroundSound.Play();

    }

    public void finishGame()
    {
        PlayerRecordData newRecord = new PlayerRecordData(_playerData.playerName, _playerData.playerScore);
        _playersRecords.saveNewPlayerRecord(newRecord);
        _playerData.cleanPlayer();
        fadingController.startFade("SelectLevelScreen", false);
    }

    public void nextLevel()
    {
        _playerData.selectedLevelIndex = _playerData.selectedLevelIndex + 1;
        fadingController.startFade("MainGameScreen", false);
    }

    public void replayLevel()
    {
        fadingController.startFade("MainGameScreen", false);
    }

    public void goToSelectLevelScreen()
    {
        fadingController.startFade("SelectLevelScreen", false);
    }

    public void goToSelectLevelScreenFromPause()
    {
        _playerData.playerScore = _playerStartScore;
        fadingController.startFade("SelectLevelScreen", false);
    }

}
