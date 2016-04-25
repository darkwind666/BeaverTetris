using UnityEngine;
using UnityEngine.UI;

public class MainMenuController : MonoBehaviour {

    public FadingScript fadingController;

    public GameObject selectLevelButton;
    public GameObject soundSettingsPopUp;

    public Slider musicSlider;
    public Slider effectsSlider;

    public AudioSource buttonClickEffect;
    public AudioSource backgroundSound;

    GamePlayerDataController _playerData;

    public string selectLevelSceneName;

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        if (_playerData.playerExist == false) {
            selectLevelButton.SetActive(false);
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
        _playerData.cleanPlayer();
        fadingController.startFade(selectLevelSceneName, false);
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
