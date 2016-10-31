using System;
using Assets.Mediation_SDK.Library;
using UnityEngine;
using UnityEngine.UI;
using System.Collections.Generic;
using System.Collections;

namespace Assets.Mediation_SDK.Demo
{
#if UNITY_ANDROID
    public class Demo : MonoBehaviour
    {
        private static int BTN_WIDHT = 300;
        private static int BTN_HEIGHT = 100;
        private static int TEXT_SIZE = 25;

        private Banner mTopBanner;
        private Banner mBottomBanner;
        private Interstitial mInterstitial;
        private Interstitial mInterstitialVideo;
        private NativeAd mNativeAd;

        private bool showNativeAd = false;
        private MainThreadLooper mMainThreadLooper;

        void Start()
        {
            mMainThreadLooper = new MainThreadLooper();
            AdSDK.start();
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

        void OnGUI()
        {
            GUI.skin.button.fontSize = TEXT_SIZE;
            GUI.skin.textArea.fontSize = TEXT_SIZE;

            GUILayout.Box("Top Banner Show Area", GUILayout.Width(Screen.width), GUILayout.Height(200));
            GUILayout.BeginScrollView(new Vector2(0, 0));
            {
                if (GUILayout.Button("Show Top Banner", GUILayout.Width(BTN_WIDHT), GUILayout.Height(BTN_HEIGHT)))
                {
                    if (mTopBanner == null)
                    {
                        mTopBanner = new Banner();
                        mTopBanner.setShowPos(0,0);
                        mTopBanner.setListener(new BannerAdListener(mTopBanner));
                    }
                    AdRequest adRequest = new AdRequest.Builder()//
                        .pub("ssr@debugbanner")//
                        .build();
                    mTopBanner.load(adRequest);
                    Debug.Log("Demo::start load top banner!");
                }
                if (GUILayout.Button("Show Bottom Banner", GUILayout.Width(BTN_WIDHT), GUILayout.Height(BTN_HEIGHT)))
                {
                    if (mBottomBanner == null)
                    {
                        mBottomBanner = new Banner();
                        int dpi = GetScreenDensityDpi();
                        int y = (int)(50 * (dpi / 160));
                        mBottomBanner.setShowPos(0, Screen.height - y);
                        mBottomBanner.setListener(new BannerAdListener(mBottomBanner));
                    }
                    AdRequest adRequest = new AdRequest.Builder()//
                        .pub("ssr@debugbanner")//
                        .build();
                    mBottomBanner.load(adRequest);
                    Debug.Log("Demo::start load bottom banner!");
                }
                if (GUILayout.Button("Show Interstitial", GUILayout.Width(BTN_WIDHT), GUILayout.Height(BTN_HEIGHT)))
                {
                    if (mInterstitial == null)
                    {
                        mInterstitial = new Interstitial();
                        mInterstitial.setListener(new InterstitialAdListener(mInterstitial));
                    }
                    AdRequest adRequest = new AdRequest.Builder()//
                        .pub("ssr@debuginterstitial")//
                        .build();
                    mInterstitial.load(adRequest);
                    Debug.Log("Demo::start load interstitial!");
                }
                if (GUILayout.Button("Show Video", GUILayout.Width(BTN_WIDHT), GUILayout.Height(BTN_HEIGHT)))
                {
                    if (mInterstitialVideo == null)
                    {
                        mInterstitialVideo = new Interstitial();
                        mInterstitialVideo.setListener(new InterstitialAdListener(mInterstitialVideo));
                    }
                    AdRequest adRequest = new AdRequest.Builder()//
                        .pub("ssr@debugvideo")//
                        .build();
                    mInterstitialVideo.load(adRequest);
                    Debug.Log("Demo::start load video!");
                }

                if (GUILayout.Button("Show Native", GUILayout.Width(BTN_WIDHT), GUILayout.Height(BTN_HEIGHT)))
                {
                    //StopAllCoroutines and StartCoroutine should run on Main Thread
                    mMainThreadLooper.Post(() => {
                    if (mNativeAd == null)
                        {
                            mNativeAd = new NativeAd();
                            mNativeAd.setListener(new NativeAdListener(delegate (Ad ad)
                            {
                                mMainThreadLooper.Post(() => {
                                showNativeAd = true;
                                    Debug.Log("Demo::onNativeAdLoaded_[icon_url:" + mNativeAd.getIconUrl() + "]");
                                    if (mNativeAd.getIconUrl() != null && mNativeAd.getIconUrl().Length > 0)
                                    {
                                        StartCoroutine(LoadImage(mNativeAd.getIconUrl(), delegate (Texture2D texture) {
                                            mIconBg = texture;
                                        }));
                                    }
                                    CoverImage cover = mNativeAd.getFilteredCover(320, 480);
                                    if(cover == null)
                                    {
                                        Debug.Log("Demo::No image matched");
                                        List <CoverImage> covers = mNativeAd.getCovers();
                                        if(covers.Count > 0)
                                        {
                                            cover = covers[0];
                                        }
                                    }

                                    if (cover != null && cover.getUrl() != null && cover.getUrl().Length > 0)
                                    {
                                        Debug.Log("Demo::onNativeAdLoaded_[cover_url:" + cover.getUrl() + "]");
                                        StartCoroutine(LoadImage(cover.getUrl(), delegate (Texture2D texture) {
                                            mCoverBg = texture;
                                        }));
                                    }
                                });
                            }));
                        }
                        showNativeAd = false;
                        mIconBg = null;
                        mCoverBg = null;

                        StopAllCoroutines();

                        AdRequest adRequest = new AdRequest.Builder()//
                            .pub("ssr@debugnative")//
                            .build();
                        mNativeAd.load(adRequest);
                        Debug.Log("Demo::start load native ad!");
                    });
                }

                if (GUILayout.Button("Exit", GUILayout.Width(BTN_WIDHT), GUILayout.Height(BTN_HEIGHT)))
                {
                    Application.Quit();
                }

                if (showNativeAd)
                {
                    if (GUILayout.Button("Title:" + mNativeAd.getTitle(), GUILayout.Width(BTN_WIDHT), GUILayout.Height(BTN_HEIGHT)))
                    {
                        mNativeAd.manualClick();
                    }
                    GUILayout.TextArea("Description:" + mNativeAd.getDescription());
                    GUILayout.Box(mIconBg, GUILayout.Width(100), GUILayout.Height(100));
                    GUILayout.Box(mCoverBg, GUILayout.Width(600), GUILayout.Height(400));
                }
            }
            GUILayout.EndScrollView();
        }
        private Texture2D mIconBg;
        private Texture2D mCoverBg;

        public delegate void NativeAdOnImageLoadedCallback(Texture2D texture);
        private static IEnumerator LoadImage(string url, NativeAdOnImageLoadedCallback callback)
        {
            WWW www = new WWW(url);
            yield return www;
            callback(www.texture);
        }

        void Update()
        {
            mMainThreadLooper.Run();
        }

        void OnDestroy()
        {
            Debug.Log("OnDestroy!");
            // Dispose of ads when the scene is destroyed
            if (mTopBanner != null)
            {
                mTopBanner.Dispose();
            }
            if (mBottomBanner != null)
            {
                mBottomBanner.Dispose();
            }
            if (mInterstitial != null)
            {
                mInterstitial.Dispose();
            }
            if (mInterstitialVideo != null)
            {
                mInterstitialVideo.Dispose();
            }
            if (mNativeAd != null)
            {
                mNativeAd.Dispose();
            }

        }
        private class InterstitialAdListener : BaseAdListener
        {
            private Interstitial mInterstitial;
            public InterstitialAdListener(Interstitial interstitial) : base("InterstitialAdListener")
            {
                mInterstitial = interstitial;
            }
            public override void onLoaded(Ad ad)
            {
                base.onLoaded(ad);
                mInterstitial.show();
            }
        }
        private class BannerAdListener : BaseAdListener
        {
            private Banner mBanner;
            public BannerAdListener(Banner banner) : base("BannerAdListener")
            {
                mBanner = banner;
            }
            public override void onLoaded(Ad ad)
            {
                base.onLoaded(ad);
                mBanner.show();
            }
        }
        public delegate void NativeAdOnLoadedCallback(Ad ad);
        private class NativeAdListener : BaseAdListener
        {
            private NativeAdOnLoadedCallback mLoadedCallback;

            public NativeAdListener(NativeAdOnLoadedCallback callback) : base("NativeAdListener")
            {
                mLoadedCallback = callback;
            }
            public override void onLoaded(Ad ad)
            {
                base.onLoaded(ad);
                mLoadedCallback(ad);
            }
        }
    }
#endif
}