using UnityEngine;
using System.Collections;

public class WinGameConditionsController : MonoBehaviour {

    public int currentWinConditionIndex;
    public GameObject[] winConditions;

    public GameObject gameSpeedContainer;
    GameSpeedController _gameSpeedController;

    GameObject _currentWinCondition;
    GameBoard _gameBoard;


    void Start () {

        _gameSpeedController = gameSpeedContainer.GetComponent<GameSpeedController>();
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _currentWinCondition = winConditions[currentWinConditionIndex];
        _currentWinCondition.SetActive(true);

    }
	
	void Update () {
	
	}

    public void updateWithGameTime()
    {

        if (_gameBoard.gameBoardLocked == false)
        {
            IWinCondition winCondition = _currentWinCondition.GetComponent<IWinCondition>();
            if (winCondition.checkWinCondition())
            {
                _gameSpeedController.stopGame();
            }
            else
            {
                checkLoseGameCondition();
            }
        }

    }

    void checkLoseGameCondition()
    {
        if(blockExistOnFinalLine())
        {
            _gameSpeedController.stopGame();
        }
    }

    bool blockExistOnFinalLine()
    {
        bool blockExist = false;

        for(int xIndex = 0; xIndex < _gameBoard.getBoardWidth(); xIndex++)
        {
            GameObject block = _gameBoard.getObjectForXY(xIndex, _gameBoard.getBoardHeight() - 1);
            if(block)
            {
                blockExist = true;
                break;
            }
        }

        return blockExist;
    }

}
