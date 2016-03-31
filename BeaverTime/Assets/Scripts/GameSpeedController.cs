using UnityEngine;
using System.Collections;

public class GameSpeedController : MonoBehaviour {

    public bool stopGame { get; set; }

    public int standardUpdateTime;
    public int acceleratedUpdateTime;
    int _maxUpdateTime;
    int _currentUpdateState;
    int _currentStandardUpdateTime;
    GameBoard _gameBoard;

    public GameShapesSpawner shapesController;
    public PlayerInputController playerInputController;
    public FallSomeShapesController fallSomeShapesController;
    public AccelerateGameSpeedController accelerateGameSpeedController;
    public WinGameConditionsController winGameConditionsController;
    public GameObject[] moveBosses;
    public GameObject bossSpells;

    public SpellsController spellsController;

    void Start () {

        _maxUpdateTime = standardUpdateTime;
        _currentStandardUpdateTime = standardUpdateTime;
        _currentUpdateState = 0;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        stopGame = false;
    }
	
	void Update () {

        if (shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false && stopGame == false)
        {
            _currentUpdateState++;

            if (_currentUpdateState >= _maxUpdateTime)
            {
                _currentUpdateState = 0;
                playerInputController.downShape();

                foreach(GameObject boss in moveBosses)
                {
                    if(boss)
                    {
                        if (boss.activeSelf)
                        {
                            BossMovementController movementController = boss.GetComponent<BossMovementController>();
                            movementController.updateWithGameTime();
                        }
                    }
                }

                if(bossSpells)
                {
                    if(bossSpells.activeSelf)
                    {
                        BossSpellCastsController bossSpell = bossSpells.GetComponent<BossSpellCastsController>();
                        bossSpell.updateWithGameTime();
                    }
                }

                spellsController.updateWithGameTime();
                accelerateGameSpeedController.updateWithGameTime();
                fallSomeShapesController.updateWithGameTime();
                winGameConditionsController.updateWithGameTime();

            }

        }

    }

    public int getCurrentGameSpeed()
    {
        return _maxUpdateTime;
    }

    public void setAcceleratedShapeSpeed()
    {
        _maxUpdateTime = acceleratedUpdateTime;
    }

    public void stopShapeAcceleration()
    {
        _maxUpdateTime = _currentStandardUpdateTime;
    }

    public void setStandardShapeSpeed(int aSpeed)
    {
        _currentStandardUpdateTime = aSpeed;
    }

    /*
    public void stopGame()
    {
        stopGame = true;
    }

    public void continueGame()
    {
        stopGame = false;
    }
    */

}
