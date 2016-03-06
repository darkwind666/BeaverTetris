using UnityEngine;
using System.Collections;
using System;

public class RemainTimeCondition : MonoBehaviour, IWinCondition {

    public int remainTime;
    int _currentTimeState;

    void Start () {

        _currentTimeState = 0;

    }
	
	void Update () {
	
	}

    public bool checkWinCondition()
    {
        bool win = true;

        _currentTimeState++;
        if(_currentTimeState < remainTime)
        {
            win = false;
        }

        return win;
    }

}
