using UnityEngine;

public class SpellsController : MonoBehaviour {

    public GameObject removeCurrentShapeSpellContainer;
    RemoveCurrentShapeSpellController _removeCurrentShapeSpellController;

    public GameObject removeBlocksSpellContainer;
    RemoveBlocksSpellController _removeBlocksSpellController;

    public GameObject firestormSpellContainer;
    FirestormSpellController _firestormSpellController;

    void Start ()
    {
        _removeCurrentShapeSpellController = removeCurrentShapeSpellContainer.GetComponent<RemoveCurrentShapeSpellController>();
        _removeBlocksSpellController = removeBlocksSpellContainer.GetComponent<RemoveBlocksSpellController>();
        _firestormSpellController = firestormSpellContainer.GetComponent<FirestormSpellController>();
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

    public void firestormSpell()
    {
        _firestormSpellController.firestormSpell();
    }

}
