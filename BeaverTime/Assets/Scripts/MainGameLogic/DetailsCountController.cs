using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class DetailsCountController : MonoBehaviour {

    public GameShapesSpawner gameShapesSpawner;
    Text _remainDetailsCount;
    int _maxDetailsCount;

    void Start () {

        _remainDetailsCount = GetComponent<Text>();

        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel levelData = levelDataStore.getCurrentLevelData();
        _maxDetailsCount = levelData.needToPlaceDetailsCount;

    }
	
	void Update () {

        int remainDetails =  Mathf.Max(0, _maxDetailsCount - gameShapesSpawner.getFallenShapesCount());
        _remainDetailsCount.text = remainDetails.ToString();

    }
}
