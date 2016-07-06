using UnityEngine;
using System.Collections;
using AppodealAds.Unity.Api;
using AppodealAds.Unity.Common;

public class AdsController : MonoBehaviour, INonSkippableVideoAdListener {

	public GameGlobalSettings settings;
	public FinalChanceController chanceController;
	public LevelResultsController levelResultsController;
	public string vungleID;
	public string appodealID;

	bool _finalChanceAd;
	bool _simplifyGameAd;
	bool _additionalScoreAd;

	void Start () {
	
		if (settings.showVungleAds) 
		{
			Vungle.init("5771811c74088aef5400016b", "Test_iOS", vungleID);
		}

		if (settings.showAppodealAds) 
		{
			Appodeal.initialize(appodealID, Appodeal.NON_SKIPPABLE_VIDEO);
			Appodeal.setNonSkippableVideoCallbacks(this);
		}
	}

	void Update () {
	
	}

	void OnApplicationPause(bool pauseStatus) {

		if (settings.showVungleAds) 
		{
			if (pauseStatus) {
				Vungle.onPause();
			}
			else {
				Vungle.onResume();
			}
		}
	}

	void OnEnable()
	{
		if (settings.showVungleAds) 
		{
			Vungle.onAdFinishedEvent += onAdFinishedEventVungle;
		}
	}
		
	void OnDisable()
	{
		if (settings.showVungleAds) 
		{
			Vungle.onAdFinishedEvent -= onAdFinishedEventVungle;
		}
	}

	void onAdFinishedEventVungle(AdFinishedEventArgs arg)
	{
		getRewardForAd();
	}

	public void onNonSkippableVideoFinished()
	{
		getRewardForAd();
	}

	public void onNonSkippableVideoLoaded() { }
	public void onNonSkippableVideoFailedToLoad() { }
	public void onNonSkippableVideoShown() { }
	public void onNonSkippableVideoClosed() { }

	void getRewardForAd()
	{
		if(_finalChanceAd)
		{
			chanceController.getReward();
			_finalChanceAd = false;
		}

		if(_simplifyGameAd)
		{
			levelResultsController.simplifyGame();
			_simplifyGameAd = false;
		}

		if(_additionalScoreAd)
		{
			levelResultsController.getAdditionalScores();
			_additionalScoreAd = false;
		}
	}

	public bool adAvailable() {

		bool adAvailable = false;

		if(settings.showAds)
		{
			if (settings.showVungleAds) 
			{
				adAvailable = Vungle.isAdvertAvailable ();
			}

			if (settings.showAppodealAds) 
			{
				adAvailable = Appodeal.isLoaded(Appodeal.NON_SKIPPABLE_VIDEO);
			}
		}
			
		return adAvailable;
	}

	public void showFinalChanceAd() {

		_finalChanceAd = true;
		playGameAd();
	}

	public void showSimplifyGameAd() {

		_simplifyGameAd = true;
		playGameAd();
	}

	public void showAdditionalScoreAd() {

		_additionalScoreAd = true;
		playGameAd();
	}

	public void playGameAd()
	{
		if (settings.showVungleAds) 
		{
			Vungle.playAd();
		}

		if (settings.showAppodealAds) 
		{
			Appodeal.show(Appodeal.NON_SKIPPABLE_VIDEO);
		}
	}

}
