using UnityEngine;
using System.Collections;

public class GoToGameUrlController : MonoBehaviour {

    public string targetUrl;


    void Start () {
	
	}
	
	void Update () {
	
	}

    public void goToUrl()
    {
        Application.OpenURL(targetUrl);
    }

}
