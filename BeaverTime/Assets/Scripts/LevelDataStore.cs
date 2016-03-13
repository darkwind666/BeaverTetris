using UnityEngine;
using System.Collections;

public class LevelDataStore {

    GameLevelsCollection _gameLevels;
    int _selectedLevelIndex;

    public LevelDataStore(GameLevelsCollection aGameLevels)
    {
        _gameLevels = aGameLevels;
        _selectedLevelIndex = 0;
    }

    public GameLevel getCurrentLevelData()
    {
        return _gameLevels.gameLevels[_selectedLevelIndex];
    }

}
