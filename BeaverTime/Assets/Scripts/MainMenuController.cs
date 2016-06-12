using UnityEngine;
using UnityEngine.UI;

public class MainMenuController : MonoBehaviour {

    public FadingScript fadingController;

    public GameObject selectLevelButton;
    public GameObject soundSettingsPopUp;
	public GameObject endlessLevelButton;

    public Slider musicSlider;
    public Slider effectsSlider;

    public AudioSource buttonClickEffect;
    public AudioSource backgroundSound;

    GamePlayerDataController _playerData;
	PlayersDatabaseController _playersRecords;

    public string selectLevelSceneName;
	public string endlessLevelSceneName;

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		_playersRecords = ServicesLocator.getServiceForKey(typeof(PlayersDatabaseController).Name) as PlayersDatabaseController;

        if (_playerData.playerExist == false) {
            selectLevelButton.SetActive(false);
			endlessLevelButton.SetActive(false);
        }

        setupAudio();

    }

    void setupAudio()
    {
        musicSlider.value = _playerData.gameMusicVolume;
        effectsSlider.value = _playerData.gameSoundEffectsVolume;

        backgroundSound.volume = _playerData.gameMusicVolume;
        buttonClickEffect.volume = _playerData.gameSoundEffectsVolume;
    }


    void Update () {
	
	}

    public void newGameButtonPressed()
    {
		PlayerRecordData newRecord = new PlayerRecordData(_playerData.playerName, _playerData.endlessLevelPlayedTime);
		_playersRecords.saveNewPlayerRecord(newRecord);
        _playerData.cleanPlayer();
        fadingController.startFade(selectLevelSceneName, false);
    }

	public void endlessLevelButtonPressed()
	{
		_playerData.selectEndlessLevel = true;
		fadingController.startFade(endlessLevelSceneName, false);
	}

    public void settingsButtonPressed()
    {
        soundSettingsPopUp.SetActive(true);
    }

    public void exitButtonPressed()
    {
        Application.Quit();
    }

    public void closeSoundSettingsPressed()
    {
        soundSettingsPopUp.SetActive(false);
    }

    public void gameMusicVolumeChanged(float aVolume)
    {
        _playerData.gameMusicVolume = aVolume;
        _playerData.savePlayerData();
    }

    public void gameSoundEffectsVolumeChanged(float aVolume)
    {
        _playerData.gameSoundEffectsVolume = aVolume;
        _playerData.savePlayerData();
    }

}
