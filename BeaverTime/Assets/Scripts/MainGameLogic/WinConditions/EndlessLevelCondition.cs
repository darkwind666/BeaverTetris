using UnityEngine;
using System.Collections;
using UnityEngine.UI;
using DG.Tweening;

public class EndlessLevelCondition : MonoBehaviour, IWinCondition {

	public int playedTime;
	public GameObject beaver;
	public Text beaverTalk;

	public string globalRecordKey;
	public string breakRecordKey;

	int _currentPlayerRecord;
	bool _setUpNewRecord;
	bool _showGlobalRecord;
	GamePlayerDataController _playerData;

	void Start () {
		playedTime = 0;
		_playerData = ServicesLocator.getServiceForKey(typeof(GamePlayerDataController).Name) as GamePlayerDataController;
		_currentPlayerRecord = _playerData.endlessLevelPlayedTime;

		string beaverText = SmartLocalization.LanguageManager.Instance.GetTextValue(globalRecordKey);
		string score = EndlessLevelIndicatorController.endlessLevelTimeFromInt(_playerData.globalHeightScore);
		beaverTalk.text = beaverText + " " + score;
		showBeaverTalk();
	}

	void Update () {

	}

	void showBeaverTalk()
	{
		beaver.SetActive(true);

		Sequence explosionSequence = DOTween.Sequence();

		explosionSequence.AppendInterval(4);
		explosionSequence.AppendCallback(() => {

			Animator animator = beaver.GetComponent<Animator>();
			animator.SetTrigger("BackBeaver");
			_showGlobalRecord = true;
			beaver.SetActive(false);

		});

	}

	public bool checkWinCondition()
	{
		playedTime++;

		if(playedTime > _currentPlayerRecord && _setUpNewRecord == false && _currentPlayerRecord > 0 && _showGlobalRecord == true)
		{
			_setUpNewRecord = true;
			string beaverText = SmartLocalization.LanguageManager.Instance.GetTextValue(breakRecordKey);
			beaverTalk.text = beaverText;
			showBeaverTalk();
		}

		return false;
	}
}
