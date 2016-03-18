using UnityEngine;
using System.Collections;

public class GameSpeedController : MonoBehaviour {

    public int standardUpdateTime;
    public int acceleratedUpdateTime;
    int _maxUpdateTime;
    int _currentUpdateState;
    int _currentStandardUpdateTime;
    bool _stopGame;

    GameBoard _gameBoard;

    public GameObject shapesContainer;
    GameShapesSpawner _shapesController;

    public GameObject playerInputContainer;
    PlayerInputController _playerInputController;

    public GameObject fallSomeShapesContainer;
    FallSomeShapesController _fallSomeShapesController;

    public GameObject accelerateGameSpeedContainer;
    AccelerateGameSpeedController _accelerateGameSpeedController;

    public GameObject winGameConditionContainer;
    WinGameConditionsController _winGameConditionsController;

    public GameObject[] moveBosses;
    public GameObject bossSpells;

    public GameObject spellsContainer;
    SpellsController _spellsController;

    void Start () {

        _maxUpdateTime = standardUpdateTime;
        _currentStandardUpdateTime = standardUpdateTime;
        _currentUpdateState = 0;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _shapesController = shapesContainer.GetComponent<GameShapesSpawner>();
        _playerInputController = playerInputContainer.GetComponent<PlayerInputController>();
        _fallSomeShapesController = fallSomeShapesContainer.GetComponent<FallSomeShapesController>();
        _accelerateGameSpeedController = accelerateGameSpeedContainer.GetComponent<AccelerateGameSpeedController>();
        _winGameConditionsController = winGameConditionContainer.GetComponent<WinGameConditionsController>();
        _spellsController = spellsContainer.GetComponent<SpellsController>();
        _stopGame = false;
    }
	
	void Update () {

        if (_shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false && _stopGame == false)
        {
            _currentUpdateState++;

            if (_currentUpdateState >= _maxUpdateTime)
            {
                _currentUpdateState = 0;
                _playerInputController.downShape();

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

                _spellsController.updateWithGameTime();
                _accelerateGameSpeedController.updateWithGameTime();
                _fallSomeShapesController.updateWithGameTime();
                _winGameConditionsController.updateWithGameTime();

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

    public void stopGame()
    {
        _stopGame = true;
    }

}
