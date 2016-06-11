using UnityEngine;
using System.Collections;

public class PlayerSpellsPadController : MonoBehaviour {

    public GameShapesSpawner shapesController;
    public SpellsController spellsController;
    public GameObject[] playerSpells;
    public string buttonCode { get; set; }

    GamePlayerDataController _gamePlayerData;
    GameBoard _gameBoard;

    const string spell1 = "RemoveShape";
    const string spell2 = "RemoveRandomBlocks";
    const string spell3 = "FirestormSpell";
    const string spell4 = "CohessionSpell";

    void Start () {

        _gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
        _gameBoard = ServicesLocator.getServiceForKey(typeof(GameBoard).Name) as GameBoard;
		showAvailableSpells();
    }
	
	void Update () {

        if (shapesController.currentShapeAvailable() && _gameBoard.gameBoardLocked == false)
        {
            checkUserInput();
        }
    }

	void showAvailableSpells()
	{
		if (_gamePlayerData.selectEndlessLevel) {

			foreach (GameObject spell in playerSpells) {
				spell.SetActive (true);
			}

		} else {

			for (int spellIndicatorIndex = 0; spellIndicatorIndex < _gamePlayerData.getPlayerSpellsCount(); spellIndicatorIndex++)
			{
				GameObject spellIndicator = playerSpells[spellIndicatorIndex];
				spellIndicator.SetActive(true);
			}

		}
	}

    void checkUserInput()
    {
        if (Input.GetButtonDown(spell1) || buttonCode == spell1)
        {
            spellsController.removeCurrentShapeSpell();
        }
        else if (Input.GetButtonDown(spell2) || buttonCode == spell2)
        {
            spellsController.removeRandomBlocksSpell();
        }
        else if (Input.GetButtonDown(spell3) || buttonCode == spell3)
        {
            spellsController.firestormSpell();
        }
        else if (Input.GetButtonDown(spell4) || buttonCode == spell4)
        {
            spellsController.cohessionSpell();
        }

        buttonCode = "";
    }
}
