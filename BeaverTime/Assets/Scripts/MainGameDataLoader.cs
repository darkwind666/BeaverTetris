using UnityEngine;
using System.Collections;

public class MainGameDataLoader : MonoBehaviour {

    public int shapeSideInBlocks;

    void Awake ()
    {
        GameBoard newGameBoard = new GameBoard(shapeSideInBlocks);
        ServicesLocator.setServiceForKey(newGameBoard, typeof(GameBoard).Name);
    }

	void Start () {
	
	}
	
	void Update () {
	
	}
}
