using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class FallSomeShapesIndicatorController : MonoBehaviour {

	public FallSomeShapesController shapesController;

	Image circularIndicator;
	public GameObject awardText;

	void Start () {

		circularIndicator = GetComponent<Image>();
		circularIndicator.fillAmount = 1f;

		checkActiveEvent();
	}

	void Update () {

		circularIndicator.fillAmount = 1.0f - (float)shapesController.currentUpdateState / (float)shapesController.maxUpdateTime;
	}

	void checkActiveEvent()
	{
		LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
		GameLevel level = levelData.getCurrentLevelData();

		bool eventActive = false;

		foreach (GameEvent gameEvent in level.levelEvents)
		{
			if (gameEvent.gameEventType == shapesController.eventType)
			{
				eventActive = true;
				break;
			}
		}

		if(eventActive == false)
		{
			gameObject.SetActive(false);
		}
	}

	public void breakFallShapesEvent()
	{
		float breakPart = 1.0f - (float)shapesController.currentUpdateState / (float)shapesController.maxUpdateTime;
		float breakReward = (float)shapesController.negativeMomentReward * breakPart;
		int reward = (int)breakReward;

		shapesController.breakNegativeMomentWithReward(reward);

		Text text = awardText.GetComponent<Text>();
		text.text = reward.ToString();

		Animator awardTextAnimator = awardText.GetComponent<Animator>();
		awardTextAnimator.SetTrigger("ShowScore");
	}
}
