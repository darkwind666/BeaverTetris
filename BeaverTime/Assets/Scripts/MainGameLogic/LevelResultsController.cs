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
	public EndlessLevelCondition endlessLevelCondition;
	public GlobalLeaderboardController globalLeaderboardController;
	public int endlessLevelStartScore;
	public AdsController adsController;
	public GameObject simplifyGameButton;

	public GameObject loseGameAdditionalScore;
	public GameObject winGameAdditionalScore;

    GamePlayerDataController _playerData;
    GameLevel _currentLevelData;

    const string escape = "Cancel";
	string _previousScreen;

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		LevelDataStore levelsDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        _currentLevelData = levelsDataStore.getCurrentLevelData();
        _playerData.playerStartLevelScore = _playerData.playerScore;
		_previousScreen = "SelectLevelScreen";

		if (_playerData.selectEndlessLevel) 
		{
			_playerData.playerScore = endlessLevelStartScore;
			_previousScreen = "MainMenuScreen";
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

			if(adsController.adAvailable())
			{
				winGameAdditionalScore.SetActive(true);
			}
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

		if(adsController.adAvailable())
		{
			simplifyGameButton.SetActive(true);
			loseGameAdditionalScore.SetActive(true);
		}
    }

	public void finishEndlessLevel()
	{
		_playerData.playerScore = _playerData.playerStartLevelScore;
		saveEndlessLevelResult();

		_playerData.savePlayerData();
		gameSpeedController.stopGame = true;
		resultPopUp.SetActive(true);
		GameObject result = results[3];
		result.SetActive(true);
		_playerData.selectEndlessLevel = false;

		gameAnaliticsController.sendFinishEndlessLevelMessage();
	}

    public void nextLevel()
    {
        _playerData.selectedLevelIndex = _playerData.selectedLevelIndex + 1;
        fadingController.startFade("MainGameScreen", false);
    }

    public void goToSelectLevelScreenFromPause()
    {
		if (_playerData.selectEndlessLevel) 
		{
			saveEndlessLevelResult();
		} 

        _playerData.playerScore = _playerData.playerStartLevelScore;
		_playerData.selectEndlessLevel = false;
        _playerData.savePlayerData();
		fadingController.startFade(_previousScreen, false);
    }

	void saveEndlessLevelResult()
	{
		GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		if (playerData.endlessLevelPlayedTime < endlessLevelCondition.playedTime) 
		{
			playerData.endlessLevelPlayedTime = endlessLevelCondition.playedTime;
			PlayerRecordData newRecord = new PlayerRecordData (playerData.playerName, playerData.endlessLevelPlayedTime);
			PlayersDatabaseController playersRecords = ServicesLocator.getServiceForKey (typeof(PlayersDatabaseController).Name) as PlayersDatabaseController;
			playersRecords.saveNewPlayerRecord (newRecord);
			globalLeaderboardController.sendPlayerRecord();
		}
	}

	public void showSimplifyGameAd()
	{
		if (adsController.adAvailable()) 
		{
			simplifyGameButton.SetActive(false);
			adsController.showSimplifyGameAd();
		}
	}

	public void showAdditionalScoreAd()
	{
		if (adsController.adAvailable()) 
		{
			
		}
	}

	public void simplifyGame()
	{
		_playerData.simplifyLevel = true;
	}

	public void getAdditionalScores()
	{
		_playerData.playerScore = _playerData.playerScore + 100;
		_playerData.savePlayerData();
	}

}
