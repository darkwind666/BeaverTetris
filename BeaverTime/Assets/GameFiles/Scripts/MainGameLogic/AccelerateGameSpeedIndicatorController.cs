using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class AccelerateGameSpeedIndicatorController : MonoBehaviour {

	public AccelerateGameSpeedController speedController;

	Image circularIndicator;
	public GameObject awardText;

	void Start () {

		circularIndicator = GetComponent<Image>();
		circularIndicator.fillAmount = 1f;

		checkActiveEvent();
	}

	void Update () {
	
		circularIndicator.fillAmount = 1.0f - (float)speedController.currentUpdateState / (float)speedController.maxUpdateTime;
	}

	void checkActiveEvent()
	{
		LevelDataStore levelData = ServicesLocator.getServiceForKey(typeof(LevelDataStore).Name) as LevelDataStore;
		GameLevel level = levelData.getCurrentLevelData();

		bool eventActive = false;

		foreach (GameEvent gameEvent in level.levelEvents)
		{
			if (gameEvent.gameEventType == speedController.eventType)
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

	public void breakAccelerateEvent()
	{
		if (speedController.activeAcceleration == false) 
		{
			float breakPart = 1.0f - (float)speedController.currentUpdateState / (float)speedController.maxUpdateTime;
			float breakReward = (float)speedController.negativeMomentReward * breakPart;
			int reward = (int)breakReward;

			speedController.breakNegativeMomentWithReward(reward);

			Text text = awardText.GetComponent<Text>();
			text.text = reward.ToString();

			Animator awardTextAnimator = awardText.GetComponent<Animator>();
			awardTextAnimator.SetTrigger("ShowScore");
		}
	}

}
