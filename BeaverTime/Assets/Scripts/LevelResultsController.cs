using UnityEngine;
using System.Collections;

public class LevelResultsController : MonoBehaviour {

    public FadingScript fadingController;
    
    void Start () {
	
	}
	
	
	void Update () {
	
	}

    public void goToSelectLevelScreen()
    {
        fadingController.startFade("SelectLevelScreen", false);
    }

}
