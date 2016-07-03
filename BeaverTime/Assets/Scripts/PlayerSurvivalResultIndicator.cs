using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class PlayerSurvivalResultIndicator : MonoBehaviour {

	public Text resultSource;
	Text _resultText;

	void Start () {
	
		_resultText = GetComponent<Text>();
		_resultText.text = resultSource.text;

	}
	
	void Update () {
	
	}
}
