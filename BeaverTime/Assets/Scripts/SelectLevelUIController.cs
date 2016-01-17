using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using System.Collections;
using System;


public class SelectLevelUIController : MonoBehaviour {

    public FadingScript fadingController;

    public GameObject background;
    public GameObject buttonClick;

    public GameObject beaverOnRaft;
    public GameObject[] beaverPositions;

    public GameObject newPlayerPopUp;
    public InputField newPlayerNameSource;

    public GameObject animationContainer;

    public Text playerName;
    public Text playerScore;


    public void backButtonPressed()
    {
        fadingController.startFade("MainMenuScreen", false);
    }

    public void selectLevelButtonPressedWithIndex(int aIndex)
    {

    }

    public void setNewPlayer()
    {
        string newPlayerName = newPlayerNameSource.text;

        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        playerData.createNewPlayerWithName(newPlayerName);

        setupPlayerStatusPad();
        newPlayerPopUp.SetActive(false);
        SelectLevelAnimationController animationController = animationContainer.GetComponent<SelectLevelAnimationController>();
        animationController.playStartAnimation();
    }

	void Start () {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        setUpBeaverPositionOnRaftWithPlayerData(playerData);
        setupSoundWithPlayerData(playerData);
        setupCreatePlayerPopUpWithPlayerData(playerData);
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
        AudioSource buttonClickEffect = buttonClick.GetComponent<AudioSource>();
        AudioSource backgroundSound = background.GetComponent<AudioSource>();

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

}
