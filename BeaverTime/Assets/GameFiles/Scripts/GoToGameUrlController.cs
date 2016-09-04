using UnityEngine;
using System.Collections;

public class GoToGameUrlController : MonoBehaviour {

    public string targetUrl;
	public bool goToPaidGame;
	public bool goToReviewGame;
	public GameGlobalSettings gameSettings;


    void Start () {
	
	}
	
	void Update () {
	
	}

    public void goToUrl()
    {
		if (goToPaidGame) 
		{
			#if UNITY_IOS
			targetUrl = gameSettings.appStoreHD;
			#endif 

			#if UNITY_ANDROID
			targetUrl = gameSettings.googlePlayHD;
			#endif 
		}

		if (goToReviewGame) 
		{
			if (gameSettings.paidGame) 
			{
				#if UNITY_IOS
				targetUrl = gameSettings.appStoreHD;
				#endif 

				#if UNITY_ANDROID
				targetUrl = gameSettings.googlePlayHD;
				#endif

				#if UNITY_WP_8_1 || UNITY_WINRT_8_1
				targetUrl = gameSettings.windowsPhoneStoreHD;
				#endif
			} 
			else 
			{
				#if UNITY_IOS
				targetUrl = gameSettings.appStoreFree;
				#endif 

				#if UNITY_ANDROID
				targetUrl = gameSettings.googlePlayFree;
				#endif

				#if UNITY_WP_8_1 || UNITY_WINRT_8_1
				targetUrl = gameSettings.windowsPhoneStoreFree;
				#endif
			}
		}
		
        Application.OpenURL(targetUrl);
    }

}
