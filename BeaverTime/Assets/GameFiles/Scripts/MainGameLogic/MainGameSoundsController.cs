using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class MainGameSoundsController : MonoBehaviour {

    public Slider musicSlider;
    public Slider effectsSlider;
    public AudioSource[] backgroundMusicTracks;
    public AudioSource[] soundEffects;
    public AudioSource backgroundSound;

    GamePlayerDataController _playerData;
    
    

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        backgroundSound = getLevelBackgroundMusic();
        backgroundSound.Play();
        setupAudio();

    }
	
	void Update () {
	
	}

    AudioSource getLevelBackgroundMusic()
    {
        int randomIndex = Random.Range(0, backgroundMusicTracks.Length);
        return backgroundMusicTracks[randomIndex];
    }

    void setupAudio()
    {
        musicSlider.value = _playerData.gameMusicVolume;
        effectsSlider.value = _playerData.gameSoundEffectsVolume;

        backgroundSound.volume = _playerData.gameMusicVolume;

        foreach (AudioSource soundEffect in soundEffects)
        {
            soundEffect.volume = _playerData.gameSoundEffectsVolume;
        }

    }

    public void gameMusicVolumeChanged(float aVolume)
    {
        _playerData.gameMusicVolume = aVolume;
        _playerData.savePlayerData();
        backgroundSound.volume = aVolume;
    }

    public void gameSoundEffectsVolumeChanged(float aVolume)
    {
        _playerData.gameSoundEffectsVolume = aVolume;
        _playerData.savePlayerData();

        foreach (AudioSource soundEffect in soundEffects)
        {
            soundEffect.volume = aVolume;
        }

    }

}
