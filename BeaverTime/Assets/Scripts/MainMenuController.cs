using UnityEngine;
using UnityEngine.UI;

public class MainMenuController : MonoBehaviour {

    public FadingScript fadingController;

    public GameObject selectLevelButton;
    public GameObject soundSettingsPopUp;

    public GameObject background;
    public GameObject buttonClick;

    public Slider musicSlider;
    public Slider effectsSlider;

    GamePlayerDataController _playerData;
    AudioSource _buttonClickEffect;
    AudioSource _backgroundSound;

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        _buttonClickEffect = buttonClick.GetComponent<AudioSource>();
        _backgroundSound = background.GetComponent<AudioSource>();

        if (_playerData.playerExist == false) {
            selectLevelButton.SetActive(false);
        }

        setupAudio();

    }

    void setupAudio()
    {
        musicSlider.value = _playerData.gameMusicVolume;
        effectsSlider.value = _playerData.gameSoundEffectsVolume;

        _backgroundSound.volume = _playerData.gameMusicVolume;
        _buttonClickEffect.volume = _playerData.gameSoundEffectsVolume;
    }


    void Update () {
	
	}

    public void newGameButtonPressed()
    {
        _playerData.cleanPlayer();
        fadingController.startFade("SelectLevelScreen", false);
    }

    public void selectLevelButtonPressed()
    {
        fadingController.startFade("SelectLevelScreen", false);
    }

    public void recordsButtonPressed()
    {

    }

    public void settingsButtonPressed()
    {
        soundSettingsPopUp.SetActive(true);
    }

    public void developersButtonPressed()
    {

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
