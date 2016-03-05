using UnityEngine;
using System.Collections;

public class BossSpellCastsController : MonoBehaviour {

    public int bossSpellInterval;
    int _currentUpdateState;
    GameBoard _gameBoard;

    public GameObject addLineSpellContainer;
    AddLineToBoardBottomSpell _addLineToBoardBottomSpell;

    public GameObject damageToPlayerSpellContainer;
    DamageToPlayerSpell _damageToPlayerSpell;

    void Start () {

        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
        _currentUpdateState = 0;
        _addLineToBoardBottomSpell = addLineSpellContainer.GetComponent<AddLineToBoardBottomSpell>();
        _damageToPlayerSpell = damageToPlayerSpellContainer.GetComponent<DamageToPlayerSpell>();

    }
	
	void Update () {
        
    }

    public void updateWithGameTime()
    {
        if (_gameBoard.gameBoardLocked == false)
        {
            _currentUpdateState++;

            if (_currentUpdateState >= bossSpellInterval)
            {
                _currentUpdateState = 0;
                castSpell();
            }
        }
    }

    void castSpell()
    {
        int randomNumber = Random.Range(0, 2);
        if (randomNumber == 0)
        {
            _addLineToBoardBottomSpell.castSpell();
        }
        else
        {
            _damageToPlayerSpell.castSpell();
        }
    }

}
