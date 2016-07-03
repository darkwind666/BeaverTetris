using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using System.Collections;
using System;


public class SelectLevelUIController : MonoBehaviour {

    public FadingScript fadingController;

    public AudioSource backgroundSound;
    public AudioSource buttonClickEffect;

    public GameObject beaverOnRaft;
    public GameObject[] beaverPositions;

    public GameObject newPlayerPopUp;
    public InputField newPlayerNameSource;

    public SelectLevelAnimationController animationController;

    public Text playerName;
    public Text playerScore;

    public GameAnaliticsController gameAnaliticsController;

    public string mainGameSceneName;

    GamePlayerDataController _playerData;


	void Start ()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        setUpBeaverPositionOnRaftWithPlayerData(playerData);
        setupSoundWithPlayerData(playerData);
        setupCreatePlayerPopUpWithPlayerData(playerData);
        _playerData = playerData;
        setupPlayerStatusPad();
    }

    void setUpBeaverPositionOnRaftWithPlayerData(GamePlayerDataController aPlayerData)
    {
        int comletedLevelsCount = aPlayerData.completedLevelsCount;
        beaverOnRaft.transform.localPosition = beaverPositions[comletedLevelsCount].transform.localPosition;
    }

    void setupCreatePlayerPopUpWithPlayerData(GamePlayerDataController aPlayerData)
    {
        if (aPlayerData.playerExist == false)
        {
            newPlayerPopUp.SetActive(true);
        }
    }

    void setupSoundWithPlayerData(GamePlayerDataController aPlayerData)
    {
        backgroundSound.volume = aPlayerData.gameMusicVolume;
        buttonClickEffect.volume = aPlayerData.gameSoundEffectsVolume;
    }

    void setupPlayerStatusPad()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        if (playerData.playerExist)
        {
            playerName.text = playerData.playerName;
            playerScore.text = playerData.playerScore.ToString();
        }
    }

    void Update () {
	
	}

    public void setNewPlayer()
    {
        string newPlayerName = newPlayerNameSource.text;

        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        playerData.createNewPlayerWithName(newPlayerName);

        gameAnaliticsController.sendCreateNewPlayerMessage();

        setupPlayerStatusPad();
        newPlayerPopUp.SetActive(false);
        animationController.playStartAnimation();
    }

    public void selectLevelButtonPressedWithIndex(int aIndex)
    {
        _playerData.selectedLevelIndex = aIndex;
        fadingController.startFade(mainGameSceneName, false);
    }

}
