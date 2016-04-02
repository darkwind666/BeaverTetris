using UnityEngine;
using System.Collections;

public class LevelDataStore {

    GameLevelsCollection _gameLevels;
    int _selectedLevelIndex;

    public LevelDataStore(GameLevelsCollection aGameLevels)
    {
        _gameLevels = aGameLevels;
        GamePlayerDataController playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        _selectedLevelIndex = playerData.selectedLevelIndex;
    }

    public GameLevel getCurrentLevelData()
    {
        return _gameLevels.gameLevels[_selectedLevelIndex];
    }

}
