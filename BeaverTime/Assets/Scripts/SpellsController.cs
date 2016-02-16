using UnityEngine;

public class SpellsController : MonoBehaviour {

    public GameObject removeCurrentShapeSpellContainer;
    RemoveCurrentShapeSpellController _removeCurrentShapeSpellController;

    public GameObject removeBlocksSpellContainer;
    RemoveBlocksSpellController _removeBlocksSpellController;

    public GameObject firestormSpellContainer;
    FirestormSpellController _firestormSpellController;

    public GameObject cohessionSpellContainer;
    CohessionSpellController _cohessionSpellController;

    void Start ()
    {
        _removeCurrentShapeSpellController = removeCurrentShapeSpellContainer.GetComponent<RemoveCurrentShapeSpellController>();
        _removeBlocksSpellController = removeBlocksSpellContainer.GetComponent<RemoveBlocksSpellController>();
        _firestormSpellController = firestormSpellContainer.GetComponent<FirestormSpellController>();
        _cohessionSpellController = cohessionSpellContainer.GetComponent<CohessionSpellController>();
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

    public void cohessionSpell()
    {
        _cohessionSpellController.cohessionSpell();
    }

}
