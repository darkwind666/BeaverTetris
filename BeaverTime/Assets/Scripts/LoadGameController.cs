using UnityEngine;
using UnityEngine.UI;

public class LoadGameController : MonoBehaviour {

    public float time;

    Image circularLoader;

    void Start () {

        circularLoader = GetComponent<Image>();
        circularLoader.fillAmount = 1f;

    }
	
	void Update () {

        if (circularLoader.fillAmount > 0f)
        {

            circularLoader.fillAmount -= Time.deltaTime / time;

        }

	}
}
