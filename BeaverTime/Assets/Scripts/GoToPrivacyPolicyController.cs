using UnityEngine;
using System.Collections;

public class GoToPrivacyPolicyController : MonoBehaviour {

    public string privacyPolicyUrl;


    void Start () {
	
	}
	
	void Update () {
	
	}

    public void goToPrivacyPolicy()
    {
        Application.OpenURL(privacyPolicyUrl);
    }

}
