using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PauseGameController : MonoBehaviour {

    public GameObject pausePopUp;
    public Button closePausePopUpButton;

    Button _pauseButton;

    const string pause = "Pause";

    void Start () {

        _pauseButton = GetComponent<Button>();

    }
	
	void Update ()
    {
        if (Input.GetButtonDown(pause))
        {

            if(pausePopUp.activeSelf)
            {
                closePausePopUpButton.onClick.Invoke();
            }
            else
            {
                _pauseButton.onClick.Invoke();
            }
            
        }
    }

}
