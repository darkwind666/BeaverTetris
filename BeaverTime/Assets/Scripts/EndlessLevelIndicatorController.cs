using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class EndlessLevelIndicatorController : MonoBehaviour {

	public EndlessLevelCondition endlessLevelCondition;

	Text _playedTimeCount;

	void Start () {

		_playedTimeCount = GetComponent<Text>();

	}

	void Update () {
		_playedTimeCount.text = EndlessLevelIndicatorController.endlessLevelTimeFromInt(endlessLevelCondition.playedTime);
	}

	public static string endlessLevelTimeFromInt(int aTime)
	{
		int hoursCount = aTime / 3600;
		int minutesCount = (aTime - 3600 * hoursCount) / 60;
		int secondsCount = aTime - (3600 * hoursCount + minutesCount * 60);
		string timeDescription = hoursCount.ToString() + ":" + minutesCount.ToString() + ":" + secondsCount.ToString();
		return timeDescription;
	}
}
