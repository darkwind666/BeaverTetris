using UnityEngine;
using System.Collections;

public class FinalChanceController : MonoBehaviour {

	public GameGlobalSettings settings;
	public GameObject button;
	public RemoveBlocksSpellController spellController;
	public AdsController adsController;
	public int showButtonTime;

	GameBoard _gameBoard;
	int _currentTimeState;

	void Start () {
	
		_gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
		_currentTimeState = 0;
	}

	void Update () {
	
	}

	public void updateWithGameTime()
	{
		if(_gameBoard.gameBoardLocked == false && settings.showAds)
		{
			if (button.activeSelf == false)
			{
				int randomExplosionIndex = Random.Range(0, 4);
				if(blockExistOnFinalLine() && adsController.adAvailable() == true && randomExplosionIndex == 2)
				{
					button.SetActive (true);
				}
			}

			if(button.activeSelf)
			{
				_currentTimeState++;
				if(_currentTimeState > showButtonTime)
				{
					_currentTimeState = 0;
					button.SetActive(false);
				}
			}
		}
	}

	bool blockExistOnFinalLine()
	{
		bool blockExist = false;

		for(int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
		{
			GameObject block = _gameBoard.getObjectForXY(xIndex, _gameBoard.getBoardHeight() - 3);
			if(block)
			{
				blockExist = true;
				break;
			}
		}

		return blockExist;
	}

	public void showAd()
	{
		_currentTimeState = 0;
		button.SetActive(false);
		adsController.showFinalChanceAd();
	}

	public void getReward()
	{
		spellController.removeAllBlocks();
	}
}
