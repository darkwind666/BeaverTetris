using System;
using UnityEngine;
using AppodealAds.Unity.Api;
using AppodealAds.Unity.Common;

// Example script showing how to invoke the Appodeal Ads Unity plugin.
public class AppodealDemo : MonoBehaviour, IInterstitialAdListener, IBannerAdListener, ISkippableVideoAdListener, IRewardedVideoAdListener
{
	
	#if UNITY_EDITOR && !UNITY_ANDROID && !UNITY_IPHONE
		string appKey = "";
	#elif UNITY_ANDROID
		string appKey = "fee50c333ff3825fd6ad6d38cff78154de3025546d47a84f";
	#elif UNITY_IPHONE
		string appKey = "dee74c5129f53fc629a44a690a02296694e3eef99f2d3a5f";
	#else
		string appKey = "";
	#endif

	private bool bannerButton = false;
	private string showBannerText = "Show Banner";
	private string showRewardedVideoText = "Show Rewarded Video";
	
	void OnGUI()
	{
		float startWidth = 0.1f;
		float startHeight = 0.05f;
		float stepHeight = 0.08f;
		float buttonWidth = 0.8f;
		float buttonHeight = 0.06f;
		
		GUI.skin.button.fontSize = (int) (0.035f * Screen.height);
		Rect initializeBannerRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
		if (GUI.Button(initializeBannerRect, "Initialize " + Appodeal.getVersion()))
		{
			//Example for UserSettings usage
			UserSettings settings = new UserSettings ();
			settings.setAge(25).setBirthday ("01/01/1990").setAlcohol(UserSettings.Alcohol.NEUTRAL)
				.setSmoking(UserSettings.Smoking.NEUTRAL).setEmail("hi@appodeal.com").setFacebookId("0987654321")
					.setVkId("87654321").setGender(UserSettings.Gender.OTHER).setRelation(UserSettings.Relation.DATING)
					.setInterests("gym, cars, cinema, science").setOccupation(UserSettings.Occupation.WORK);
			
			Appodeal.setLogging(true);
			//Appodeal.setTesting(true);
			Appodeal.confirm(Appodeal.SKIPPABLE_VIDEO);
			Appodeal.setBannerCallbacks (this);
			Appodeal.setInterstitialCallbacks (this);
			Appodeal.setSkippableVideoCallbacks (this);
			Appodeal.setRewardedVideoCallbacks(this);
			Appodeal.initialize (appKey, Appodeal.INTERSTITIAL | Appodeal.BANNER | Appodeal.SKIPPABLE_VIDEO | Appodeal.REWARDED_VIDEO);
		}
		
		Rect showInterstitialRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 2) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
		if (GUI.Button(showInterstitialRect, "Show Interstitial"))
		{
			Appodeal.show(Appodeal.INTERSTITIAL);
		}
		
		Rect showVideoRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 3) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
		if (GUI.Button(showVideoRect, "Show Video"))
		{
			Appodeal.show(Appodeal.SKIPPABLE_VIDEO);
		}
		
		Rect showRewardedVideoRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 4) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
		if (GUI.Button(showRewardedVideoRect, showRewardedVideoText))
		{
			Appodeal.show(Appodeal.REWARDED_VIDEO);
		}
		
		
		Rect hideBannerRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 5) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
		if (GUI.Button(hideBannerRect, "Hide Banner"))
		{
			Appodeal.hide(Appodeal.BANNER);
			showBannerText = "Show Banner";
		}
		
		Rect showBannerRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 6) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
		if (!bannerButton) {
			if (GUI.Button(showBannerRect, showBannerText))
			{
				bannerButton = true;
			}
		} else {
			Rect showBannerTopRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 6) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
			if (GUI.Button(showBannerTopRect, "Show Banner Top"))
			{
				Appodeal.show(Appodeal.BANNER_TOP);
				showBannerText = "Showing Banner Top";
				bannerButton = false;
			}
			Rect showBannerCenterRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 7) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
			if (GUI.Button(showBannerCenterRect, "Show Banner Center"))
			{
				Appodeal.show(Appodeal.BANNER_CENTER);
				showBannerText = "Showing Banner Center";
				bannerButton = false;
			}
			Rect showBannerBottomRect = new Rect(startWidth * Screen.width, (startHeight + stepHeight * 8) * Screen.height, buttonWidth * Screen.width, buttonHeight * Screen.height);
			if (GUI.Button(showBannerBottomRect, "Show Banner Bottom"))
			{
				Appodeal.show(Appodeal.BANNER_BOTTOM);
				showBannerText = "Showing Banner Bottom";
				bannerButton = false;
			}
		}
		
	}
	
	#region Banner callback handlers
	
	public void onBannerLoaded() { print("Banner loaded"); }
	public void onBannerFailedToLoad() { print("Banner failed"); }
	public void onBannerShown() { print("Banner opened"); }
	public void onBannerClicked() { print("banner clicked"); }
	
	#endregion
	
	#region Interstitial callback handlers
	
	public void onInterstitialLoaded() { print("Interstitial loaded"); }
	public void onInterstitialFailedToLoad() { print("Interstitial failed"); }
	public void onInterstitialShown() { print("Interstitial opened"); }
	public void onInterstitialClosed() {  print("Interstitial closed"); }
	public void onInterstitialClicked() { print("Interstitial clicked"); }
	
	#endregion
	
	#region Video callback handlers
	
	public void onSkippableVideoLoaded() { print("Skippable Video loaded"); }
	public void onSkippableVideoFailedToLoad() { print("Skippable Video failed"); }
	public void onSkippableVideoShown() { print("Skippable Video opened"); }
	public void onSkippableVideoClosed() { print("Skippable Video closed"); }
	public void onSkippableVideoFinished() { print("Skippable Video finished"); }
	
	#endregion
	
	#region Non Skippable Video callback handlers
	
	public void onNonSkippableVideoLoaded() { print("NonSkippable Video loaded"); }
	public void onNonSkippableVideoFailedToLoad() { print("NonSkippable Video failed"); }
	public void onNonSkippableVideoShown() { print("NonSkippable Video opened"); }
	public void onNonSkippableVideoClosed() { print("NonSkippable Video closed"); }
	public void onNonSkippableVideoFinished() { print("NonSkippable Video finished"); }
	
	#endregion
	
	#region Rewarded Video callback handlers
	
	public void onRewardedVideoLoaded() { print("Rewarded Video loaded"); }
	public void onRewardedVideoFailedToLoad() { print("Rewarded Video failed"); }
	public void onRewardedVideoShown() { print("Rewarded Video opened"); }
	public void onRewardedVideoClosed() { print("Rewarded Video closed"); }
	public void onRewardedVideoFinished(int amount, string name) { showRewardedVideoText = "Rewarded Video Reward: " + amount + " " + name; }
	
	#endregion
}