using UnityEngine;

public class SpellsController : MonoBehaviour {

    public GameObject removeCurrentShapeSpellContainer;
    RemoveCurrentShapeSpellController _removeCurrentShapeSpellController;

    public GameObject removeBlocksSpellContainer;
    RemoveBlocksSpellController _removeBlocksSpellController;

    void Start ()
    {
        _removeCurrentShapeSpellController = removeCurrentShapeSpellContainer.GetComponent<RemoveCurrentShapeSpellController>();
        _removeBlocksSpellController = removeBlocksSpellContainer.GetComponent<RemoveBlocksSpellController>();
    }
	
	void Update () {

	}

    public void removeCurrentShapeSpell()
    {
        _removeCurrentShapeSpellController.removeCurrentShapeSpell();
    }

    public void removeRandomBlocksSpell()
    {
        _removeBlocksSpellController.removeRandomBlocksSpell();
    }

}
