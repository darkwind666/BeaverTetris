using UnityEngine;
using System.Collections;

public class MainGameDataLoader : MonoBehaviour {

    public int shapeSideInBlocks;
    public GameLevelsCollection gameLevelsCollection;

    void Awake ()
    {
        GameBoard newGameBoard = new GameBoard(shapeSideInBlocks);
        ServicesLocator.setServiceForKey(newGameBoard, typeof(GameBoard).Name);

        LevelDataStore levelDataController = new LevelDataStore(gameLevelsCollection);
        ServicesLocator.setServiceForKey(levelDataController, typeof(LevelDataStore).Name);
    }

	void Start () {
	
	}
	
	void Update () {
	
	}
}
