using UnityEngine;
using System.Collections.Generic;
using System;

public class WinBossCondition : MonoBehaviour, IWinCondition {

    public GameObject bossesContainer;

    void Start () {
	
	}
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        GameBossesController bossesController = bossesContainer.GetComponent<GameBossesController>();
        List<GameObject> bosses = bossesController.currentBosses;

        foreach(GameObject boss in bosses)
        {
            if(boss)
            {
                win = false;
                break;
            }
        }

        return win;
    }

}
