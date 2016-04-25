using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PlayerScoreController : MonoBehaviour {

    Text _text;
    GamePlayerDataController _playerData;

	void Start () {

        _text = GetComponent<Text>();
        _playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

    }
	
	void Update () {

        _text.text = _playerData.playerScore.ToString();

    }
}
