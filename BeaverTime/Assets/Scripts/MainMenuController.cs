using UnityEngine;
using System.Collections;

public class MainMenuController : MonoBehaviour {

    public GameObject selectLevelButton;

	void Start () {

        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        if(playerData.playerExist == false) {
            selectLevelButton.SetActive(false);
        }

	}
	
	void Update () {
	
	}

    public void newGameButtonPresed() {

    }

    public void selectLevelButtonPresed()
    {

    }

    public void recordsButtonPresed()
    {

    }

    public void settingsButtonPresed()
    {

    }

    public void developersButtonPresed()
    {

    }

    public void exitButtonPresed()
    {
        Application.Quit();
    }

}
