using UnityEngine;
using System.Collections;

public class LevelTutorialController : MonoBehaviour {

    public GameObject[] tutorials;
    public PlayerTutorialController playerTutorialController;

    int _currentTutorialIndex;

	void Start () {

        _currentTutorialIndex = 0;
        GameObject firstTutorial = tutorials[_currentTutorialIndex];
        firstTutorial.SetActive(true);

    }
	
	void Update () {

        if (Input.GetKeyDown("space") || Input.GetMouseButtonDown(0))
        {
            GameObject currentTutorial = tutorials[_currentTutorialIndex];
            currentTutorial.SetActive(false);
            _currentTutorialIndex++;

            if(_currentTutorialIndex > (tutorials.Length - 1))
            {
                playerTutorialController.endTutorial();
            }
            else
            {
                GameObject nextTutorial = tutorials[_currentTutorialIndex];
                nextTutorial.SetActive(true);
                playerTutorialController.nextTutorial();
            }

        }

    }

}
