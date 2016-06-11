using UnityEngine;
using System.Collections;

public class LevelDataStore {

    GameLevelsCollection _gameLevels;
    int _selectedLevelIndex;
	GamePlayerDataController _playerData;

    public LevelDataStore(GameLevelsCollection aGameLevels)
    {
        _gameLevels = aGameLevels;
		_playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		_selectedLevelIndex = _playerData.selectedLevelIndex;
    }

    public GameLevel getCurrentLevelData()
    {
		GameLevel levelData;

		if (_playerData.selectEndlessLevel) {
			levelData = _gameLevels.endlessLevel;
		} else {
			levelData = _gameLevels.gameLevels[_selectedLevelIndex];
		}

		return levelData;
    }

}
