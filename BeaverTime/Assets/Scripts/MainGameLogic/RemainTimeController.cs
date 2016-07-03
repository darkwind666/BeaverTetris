using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class RemainTimeController : MonoBehaviour {

    public RemainTimeCondition remainTimeCondition;

    Text _remainTimeCount;

    void Start () {

        _remainTimeCount = GetComponent<Text>();

    }
	
	void Update () {

        int remainTime = remainTimeCondition.remainTime - remainTimeCondition.currentTimeState;
        _remainTimeCount.text = remainTime.ToString();

    }
}
