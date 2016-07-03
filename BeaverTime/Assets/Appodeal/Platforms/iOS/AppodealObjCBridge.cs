using System;
using System.Runtime.InteropServices;

#if UNITY_IPHONE
namespace AppodealAds.Unity.iOS
{
	
	internal delegate void AppodealNativeDelegate ();
	internal delegate void AppodealRewardedVideoDidFinishDelegate (int amount, String name);
	
	internal class AppodealObjCBridge
	{
		[DllImport("__Internal")]
		internal static extern void AppodealInitializeWithTypes (string apiKey, int types);
		
		[DllImport("__Internal")]
		internal static extern bool AppodealShowAd (int style);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetAutocache (bool autocache, int types);
		
		[DllImport("__Internal")]
		internal static extern void AppodealCacheAd (int types);
		
		[DllImport("__Internal")]
		internal static extern bool AppodealIsReadyWithStyle (int style);
		
		[DllImport("__Internal")]
		internal static extern void AppodealHideBanner ();
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetInterstitialDelegate (
			AppodealNativeDelegate interstitialDidLoadAd,
			AppodealNativeDelegate interstitialDidFailToLoadAd,
			AppodealNativeDelegate interstitialDidClick,
			AppodealNativeDelegate interstitialDidDismiss,
			AppodealNativeDelegate interstitialWillPresent
			);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetVideoDelegate (
			AppodealNativeDelegate videoDidLoadAd,
			AppodealNativeDelegate videoDidFailToLoadAd,
			AppodealNativeDelegate videoWillDismiss,
			AppodealNativeDelegate videoDidFinish,
			AppodealNativeDelegate videoDidPresent
			);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetRewardedVideoDelegate(
			AppodealNativeDelegate rewardedVideoDidLoadAd,
			AppodealNativeDelegate rewardedVideoDidFailToLoadAd,
			AppodealNativeDelegate rewardedVideoWillDismiss,
			AppodealRewardedVideoDidFinishDelegate rewardedVideoDidFinish,
			AppodealNativeDelegate rewardedVideoDidPresent
			);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetBannerDelegate (
			AppodealNativeDelegate bannerDidLoadAd,
			AppodealNativeDelegate bannerDidFailToLoadAd,
			AppodealNativeDelegate bannerDidClick,
			AppodealNativeDelegate bannerDidShow
			);
		
		[DllImport("__Internal")]
		internal static extern string AppodealGetVersion ();
		
		[DllImport("__Internal")]
		internal static extern void AppodealDisableNetwork(string networkName);
		
		[DllImport("__Internal")]
		internal static extern void AppodealDisableNetworkForAdTypes(string networkName, int adTypes);
		
		[DllImport("__Internal")]
		internal static extern void AppodealDisableLocationPermissionCheck();
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetDebugEnabled(bool debugEnabled);
		
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserId(string id);

		[DllImport("__Internal")]
		internal static extern void AppodealSetUserAge(int age);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserBirthday(string birthday);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserEmail(string email);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserFacebookId(string facebookId);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserVkId(string vkId);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserGender(int gender);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserInterests(string interests);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserOccupation(int occupation);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserRelationship(int relationship);
		
		[DllImport("__Internal")]
		internal static extern void	AppodealSetUserAlcoholAttitude(int attitude);
		
		[DllImport("__Internal")]
		internal static extern void AppodealSetUserSmokingAttitude(int attitude);
	}
}
#endif