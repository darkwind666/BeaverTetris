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

        setUpPlayer();
    }

    void setUpPlayer()
    {
        GamePlayerDataController gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelDataStore.getCurrentLevelData();

        foreach (LevelSpell spell in level.levelSpells)
        {
            gamePlayerData.setPlayerSpell(spell);
        }
    }

	void Start () {
	
	}
	
	void Update () {
	
	}
}
