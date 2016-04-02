using UnityEngine;
using System.Collections;

public class LevelResultsController : MonoBehaviour {

    public FadingScript fadingController;
    public GameSpeedController gameSpeedController;
    public GameObject resultPopUp;
    public GameLevelsCollection gameLevelsCollection;
    public GameObject[] results;

    GamePlayerDataController _playerData;

    void Start () {

        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

    }
	
	
	void Update () {
	
	}

    public void winLevel()
    {
        gameSpeedController.stopGame = true;
        resultPopUp.SetActive(true);

        GameObject result;
        if (_playerData.selectedLevelIndex >= (gameLevelsCollection.gameLevels.Length - 1))
        {
            result = results[2];
        }
        else
        {
            result = results[1];
        }

        result.SetActive(true);
    }

    public void loseLevel()
    {
        gameSpeedController.stopGame = true;
        resultPopUp.SetActive(true);
        GameObject result = results[0];
        result.SetActive(true);
    }

    public void finishGame()
    {
        fadingController.startFade("SelectLevelScreen", false);
    }

    public void nextLevel()
    {
        _playerData.selectedLevelIndex = _playerData.selectedLevelIndex + 1;
        fadingController.startFade("MainGameScreen", false);
    }

    public void replayLevel()
    {
        fadingController.startFade("SelectLevelScreen", false);
    }

    public void goToSelectLevelScreen()
    {
        fadingController.startFade("SelectLevelScreen", false);
    }

}
