using UnityEngine;
using System.Collections.Generic;
using System;

public class SpellsController : MonoBehaviour {

    public GameObject removeCurrentShapeSpellContainer;
    RemoveCurrentShapeSpellController _removeCurrentShapeSpellController;

    public GameObject removeBlocksSpellContainer;
    RemoveBlocksSpellController _removeBlocksSpellController;

    public GameObject firestormSpellContainer;
    FirestormSpellController _firestormSpellController;

    public GameObject cohessionSpellContainer;
    CohessionSpellController _cohessionSpellController;

    List<Action> _spells;
    GamePlayerDataController _gamePlayerData;

    void Start ()
    {
        setSpellsData();
        setPlayerData();
    }

    void setSpellsData()
    {
        _removeCurrentShapeSpellController = removeCurrentShapeSpellContainer.GetComponent<RemoveCurrentShapeSpellController>();
        _removeBlocksSpellController = removeBlocksSpellContainer.GetComponent<RemoveBlocksSpellController>();
        _firestormSpellController = firestormSpellContainer.GetComponent<FirestormSpellController>();
        _cohessionSpellController = cohessionSpellContainer.GetComponent<CohessionSpellController>();

        _spells = new List<Action>();
        _spells.Add(() => _removeCurrentShapeSpellController.removeCurrentShapeSpell());
        _spells.Add(() => _removeBlocksSpellController.removeRandomBlocksSpell());
        _spells.Add(() => _firestormSpellController.firestormSpell());
        _spells.Add(() => _cohessionSpellController.cohessionSpell());
    }

    void setPlayerData()
    {
        _gamePlayerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;

        LevelDataStore levelDataStore = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
        GameLevel level = levelDataStore.getCurrentLevelData();

        foreach (LevelSpell spell in level.levelSpells)
        {
            _gamePlayerData.setPlayerSpell(spell);
        }
    }

    void Update () {

	}

    public void removeCurrentShapeSpell()
    {

        useSpellForIndex(0);
    }

    public void removeRandomBlocksSpell()
    {
        useSpellForIndex(1);
    }

    public void firestormSpell()
    {
        useSpellForIndex(2);
    }

    public void cohessionSpell()
    {
        useSpellForIndex(3);
    }

    void useSpellForIndex(int aSpellIndex)
    {
        if (aSpellIndex < _gamePlayerData.getPlayerSpellsCount())
        {
            Action spell = _spells[aSpellIndex];
            spell();
        }
    }

}
