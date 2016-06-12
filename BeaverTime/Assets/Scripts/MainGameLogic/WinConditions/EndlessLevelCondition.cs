using UnityEngine;
using System.Collections;

public class EndlessLevelCondition : MonoBehaviour, IWinCondition {

	public int playedTime;

	int _minuteTimeStep;

	void Start () {
		playedTime = 0;
		_minuteTimeStep = 0;
	}

	void Update () {

	}

	public bool checkWinCondition()
	{
		playedTime++;
		return false;
	}
}
