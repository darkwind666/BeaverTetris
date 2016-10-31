using UnityEngine;
using System.Collections;
using AppodealAds.Unity.Api;
using AppodealAds.Unity.Common;
using Assets.Mediation_SDK.Library;

public class AdsController : MonoBehaviour, INonSkippableVideoAdListener, AdListener {

	public GameGlobalSettings settings;
	public FinalChanceController chanceController;
	public LevelResultsController levelResultsController;

	bool _finalChanceAd;
	bool _simplifyGameAd;
	bool _additionalScoreAd;
	bool _adToBlockAd;

	BlockAdsController _currentBlockAdsController;

	private Banner _mTopBanner;
	private Interstitial _mInterstitial;
	private Interstitial _mInterstitialVideo;

	void Start () {
	
		if (settings.showVungleAds) 
		{
			#if UNITY_WP_8_1 || UNITY_WINRT_8_1
			Vungle.init("5771811c74088aef5400016b", "Test_iOS", settings.windowsPhoneStoreFreeVungleID);
			#endif    
		}

		if (settings.showAppodealAds) 
		{
			string appodealId;

			if (settings.paidGame) {

				appodealId = settings.androidHdAppodealId;

				#if UNITY_IOS
				appodealId = settings.iosHdAppodealId;
				#endif 

			} else {
				appodealId = settings.androidFreeAppodealId;

				#if UNITY_IOS
				appodealId = settings.iosFreeAppodealId;
				#endif 
			}

			Appodeal.initialize(appodealId, Appodeal.NON_SKIPPABLE_VIDEO | Appodeal.INTERSTITIAL | Appodeal.BANNER_TOP);
			Appodeal.setNonSkippableVideoCallbacks(this);
		}

		if (settings.showUnionAds) 
		{
			AdSDK.start();
		}
	}

	void Update () {
	
	}

	void OnApplicationPause(bool pauseStatus) {

		if (settings.showVungleAds) 
		{
			if (pauseStatus) {
				#if UNITY_WP_8_1 || UNITY_WINRT_8_1
				Vungle.onPause();
				#endif  
			}
			else {
				#if UNITY_WP_8_1 || UNITY_WINRT_8_1
				Vungle.onResume();
				#endif  
			}
		}
	}

	void OnEnable()
	{
		if (settings.showVungleAds) 
		{
			#if UNITY_WP_8_1 || UNITY_WINRT_8_1
			Vungle.onAdFinishedEvent += onAdFinishedEventVungle;
			#endif 
		}
	}
		
	void OnDisable()
	{
		if (settings.showVungleAds) 
		{
			#if UNITY_WP_8_1 || UNITY_WINRT_8_1
			Vungle.onAdFinishedEvent += onAdFinishedEventVungle;
			#endif 
		}
	}

	#if UNITY_WP_8_1 || UNITY_WINRT_8_1

	void onAdFinishedEventVungle(AdFinishedEventArgs arg)
	{
		getRewardForAd();
	}

	#endif 


	public virtual void onClosed(Ad ad)
	{
		getRewardForAd();
	}

	public virtual void onClicked(Ad ad) {}
	public virtual void onError(Ad ad, AdError error) {}
	public virtual void onLoaded(Ad ad) {}
	public virtual void onOpened(Ad ad) {}

	public void onNonSkippableVideoFinished() {}

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

		if(_adToBlockAd)
		{
			_currentBlockAdsController.addFinishShow();
			_adToBlockAd = false;
		}
	}

	public bool adAvailable() {

		bool adAvailable = false;

		if (settings.showVungleAds) 
		{
			#if UNITY_WP_8_1 || UNITY_WINRT_8_1
			//adAvailable = Vungle.isAdvertAvailable ();
			adAvailable = true;
			#endif 
		}

		if (settings.showAppodealAds) 
		{
			//adAvailable = Appodeal.isLoaded(Appodeal.NON_SKIPPABLE_VIDEO);
			adAvailable = true;
		}

		if (settings.showUnionAds) 
		{
			adAvailable = true;
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

	public void showAdToBlockAdFromController(BlockAdsController aBlockAdController)
	{
		_currentBlockAdsController = aBlockAdController;
		_adToBlockAd = true;
		playGameAd();
	}

	public void playGameAd()
	{
		showAds();
	}

	void showAds()
	{
		if (settings.showVungleAds) 
		{
			#if UNITY_WP_8_1 || UNITY_WINRT_8_1
			Vungle.playAd();
			#endif 
		}

		if (settings.showAppodealAds) 
		{
			Appodeal.show(Appodeal.NON_SKIPPABLE_VIDEO);
		}

		if (settings.showUnionAds) 
		{
			if (_mInterstitialVideo == null)
			{
				_mInterstitialVideo = new Interstitial();
				_mInterstitialVideo.setListener(this);
			}

			AdRequest adRequest = new AdRequest.Builder()
				.pub("hexn@beavertimeV")
				.build();
			_mInterstitialVideo.load(adRequest);
			_mInterstitialVideo.show();
		}
	}

	public void tryShowInterstitial()
	{
		int randomNumber = UnityEngine.Random.Range(0, 3);
		if(randomNumber == 0)
		{
			if (settings.showAppodealAds && settings.paidGame == false) 
			{
				if (Appodeal.isLoaded (Appodeal.INTERSTITIAL)) 
				{
					Appodeal.show(Appodeal.INTERSTITIAL);
				}
			}

			if (settings.showUnionAds && settings.paidGame == false) 
			{
				if (_mInterstitial == null)
				{
					_mInterstitial = new Interstitial();
				}

				AdRequest adRequest = new AdRequest.Builder()
					.pub("hexn@beavertimeI")
					.build();
				_mInterstitial.load(adRequest);
				_mInterstitial.show();
			}
		}
	}

	public void showInterstitial()
	{
		if (settings.showAppodealAds && settings.paidGame == false && settings.blockAds == false) 
		{
			if (Appodeal.isLoaded (Appodeal.INTERSTITIAL)) 
			{
				Appodeal.show(Appodeal.INTERSTITIAL);
			}
		}

		if (settings.showUnionAds && settings.paidGame == false && settings.blockAds == false) 
		{
			if (_mInterstitial == null)
			{
				_mInterstitial = new Interstitial();
			}

			AdRequest adRequest = new AdRequest.Builder()
				.pub("hexn@beavertimeI")
				.build();
			_mInterstitial.load(adRequest);
			_mInterstitial.show();
		}
	}

	public void showBottomBanner()
	{
		if (settings.showAppodealAds && settings.paidGame == false && settings.blockAds == false)
		{
			if (Appodeal.isLoaded (Appodeal.BANNER_TOP))
			{
				Appodeal.show(Appodeal.BANNER_TOP);
			}
		}

		if (settings.showUnionAds && settings.paidGame == false && settings.blockAds == false) 
		{
			if (_mTopBanner == null)
			{
				_mTopBanner = new Banner();
				_mTopBanner.setShowPos(0,0);
			}

			AdRequest adRequest = new AdRequest.Builder()
				.pub("hexn@beavertimeB")
				.build();
			_mTopBanner.load(adRequest);
			_mTopBanner.show();

		}
	}

	public void hideBottomBanner()
	{
		if (settings.showAppodealAds) 
		{
			Appodeal.hide(Appodeal.BANNER_TOP);
		}

		if (settings.showUnionAds) 
		{
			if (_mTopBanner != null)
			{
				_mTopBanner.Dispose();
			}
		}
	}

	int GetScreenDensityDpi()
	{
		AndroidJavaClass unityPlayer = new AndroidJavaClass("com.unity3d.player.UnityPlayer");
		AndroidJavaObject activity = unityPlayer.GetStatic<AndroidJavaObject>("currentActivity");
		AndroidJavaObject wm = activity.Call<AndroidJavaObject>("getWindowManager");
		AndroidJavaObject defaultDisplay = wm.Call<AndroidJavaObject>("getDefaultDisplay");
		AndroidJavaObject displayMetrics = new AndroidJavaObject("android.util.DisplayMetrics");
		defaultDisplay.Call("getMetrics", displayMetrics);
		return displayMetrics.Get<int>("densityDpi");
	}

}
