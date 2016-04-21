using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;

public class ESCButtonController : MonoBehaviour {

    public FadingScript fadingController;

    const string escape = "Cancel";

    bool _escButtonPressed;

    void Start ()
    {
        _escButtonPressed = false;
    }

    void Update()
    {

        if (Input.GetButtonDown(escape) && _escButtonPressed == false)
        {
            _escButtonPressed = true;
            changeSceneForEscapeButtonClick();
        }
    }

    void changeSceneForEscapeButtonClick()
    {
        string currentSceneName = SceneManager.GetActiveScene().name;
        if (currentSceneName == "GameLoadingScene" || currentSceneName == "MainMenuScreen")
        {
            Application.Quit();
        }
        else if (currentSceneName == "GameRecordsScene")
        {
            fadingController.goToScreen("MainMenuScreen");
        }
        else if (currentSceneName == "MainGameScreen")
        {
            exitFromMainGameScene();
        }
        else
        {
            goToPreviousScene();
        }
    }

    void exitFromMainGameScene()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        string previouseSceneName = playerData.popPreviousScene();

        if (playerData.playerExist)
        {
            playerData.playerScore = playerData.playerStartLevelScore;
            fadingController.goToScreen(previouseSceneName);
        }
        else
        {
            fadingController.goToScreen("MainMenuScreen");
        }
    }

    public void goToPreviousScene()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        string previouseSceneName = playerData.popPreviousScene();
        fadingController.goToScreen(previouseSceneName);
    }

    public void pushCurrentSceneName()
    {
        string currentSceneName = SceneManager.GetActiveScene().name;
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        playerData.pushCurrentSceneName(currentSceneName);
    }

    public void popPreviousSceneName()
    {
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        playerData.popPreviousScene();
    }

}
