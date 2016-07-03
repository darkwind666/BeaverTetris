using UnityEngine;
using System.Collections;

public class LevelDataStore {

    GameLevelsCollection _gameLevels;
    int _selectedLevelIndex;
	GamePlayerDataController _playerData;
	GameLevel _levelData;

	float _simplifyCoefficient =  0.3f;

    public LevelDataStore(GameLevelsCollection aGameLevels)
    {
        _gameLevels = aGameLevels;
		_playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		_selectedLevelIndex = _playerData.selectedLevelIndex;

		if (_playerData.selectEndlessLevel) {
			_levelData = _gameLevels.endlessLevel;
		} else {
			_levelData = _gameLevels.gameLevels[_selectedLevelIndex];

			if (_playerData.simplifyLevel)
			{
				_levelData.needToPlaceDetailsCount -= (int)((float)_levelData.needToPlaceDetailsCount * _simplifyCoefficient);
				_levelData.remainTimes -= (int)((float)_levelData.remainTimes * _simplifyCoefficient);
				_levelData.bossLivesCount -= (int)((float)_levelData.bossLivesCount * _simplifyCoefficient);

				for(int blockIndex = 0; blockIndex < _levelData.blocks.Length; blockIndex++)
				{
					BlocksForRemoving block = _levelData.blocks[blockIndex];
					int blocksCount = block.blocksCount - (int)((float)block.blocksCount * _simplifyCoefficient);
					_levelData.blocks[blockIndex].blocksCount = blocksCount;
				}

				_playerData.simplifyLevel = false;
			}

		}
    }

    public GameLevel getCurrentLevelData()
    {
		return _levelData;
    }

}
