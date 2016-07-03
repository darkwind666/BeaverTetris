using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PlayerAwardIndicator : MonoBehaviour {

    Text _avardText;

	void Start () {

        _avardText = GetComponent<Text>();
        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel levelData = levelDataStore.getCurrentLevelData();
        _avardText.text = levelData.levelAward.ToString();

    }
	
	void Update () {
	
	}
}
