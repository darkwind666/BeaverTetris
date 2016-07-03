//
//  AppodealInterface.m
//
//  Created by ewgenius on 4.08.15.
//  Copyright (c) 2015 Appodeal. All rights reserved.
//

#if defined(__has_include) && __has_include("UnityAppController.h")
#import "UnityAppController.h"
#else
#import "EmptyUnityAppController.h"
#endif

#import <Appodeal/Appodeal.h>
#import <Appodeal/AppodealInterstitialDelegate.h>
#import <Appodeal/AppodealBannerDelegate.h>
#import <Appodeal/AppodealVideoDelegate.h>

#import "AppodealObjCBridge.h"
#import "AppodealInterstitialDelegate.h"
#import "AppodealVideoDelegate.h"
#import "AppodealBannerDelegate.h"
#import "AppodealRewardedVideoDelegate.h"

extern UIViewController *UnityGetGLViewController();

NSString *AppodealStringFromUTF8String(const char *bytes) { return bytes ? @(bytes) : nil; }

char * AppodealUTF8StringFromString(NSString *string) {
    const char *cString = [[Appodeal getVersion] UTF8String];
    char *cStringCopy = calloc([string length]+1, 1);
    return strncpy(cStringCopy, cString, [string length]);
}

static UIViewController* RootViewController() {
    return UnityGetGLViewController();
}

static NSDateFormatter *DateFormatter() {
    static dispatch_once_t onceToken;
    static NSDateFormatter *formatter;
    dispatch_once(&onceToken, ^{
        formatter = [[NSDateFormatter alloc] init];
        formatter.dateFormat = @"dd/MM/yyyy";
    });
    
    return formatter;
}

/// AppodealAdType enum:
///   AppodealAdTypeInterstitial = 1 << 0,
///   AppodealAdTypeVideo        = 1 << 1,
///   AppodealAdTypeBanner       = 1 << 2,
///   AppodealAdTypeAll          = AppodealAdTypeInterstitial | AppodealAdTypeVideo | AppodealAdTypeBanner

void AppodealInitializeWithTypes(const char *apiKey, int types) {
    [Appodeal initializeWithApiKey:AppodealStringFromUTF8String(apiKey) types:types];
}

/// AppodealShowStyle enum:
///   AppodealShowStyleInterstitial        = 1,
///   AppodealShowStyleVideo               = 2,
///   AppodealShowStyleVideoOrInterstitial = 3,
///   AppodealShowStyleBannerTop           = 4,
///   AppodealShowStyleBannerCenter        = 5,
///   AppodealShowStyleBannerBottom        = 6

BOOL AppodealShowAd(int style) {
    return [Appodeal showAd:style rootViewController: RootViewController()];
}

void AppodealSetAutocache(BOOL autocache, int types) {
    [Appodeal setAutocache:autocache types:types];
}

void AppodealCacheAd(int types) {
    [Appodeal cacheAd:types];
}

BOOL AppodealIsReadyWithStyle(int style) {
    return [Appodeal isReadyForShowWithStyle:style];
}

void AppodealHideBanner() {
    [Appodeal hideBanner];
}

static AppodealInterstitialDelegate *AppodealInterstitialDelegateInstance;

void AppodealSetInterstitialDelegate(AppodealNativeDelegate interstitialDidLoadAd,
                                     AppodealNativeDelegate interstitialDidFailToLoadAd,
                                     AppodealNativeDelegate interstitialDidClick,
                                     AppodealNativeDelegate interstitialDidDismiss,
                                     AppodealNativeDelegate interstitialWillPresent) {
    
    AppodealInterstitialDelegateInstance = [AppodealInterstitialDelegate new];
    
    AppodealInterstitialDelegateInstance.interstitialDidLoadAdDelegate = interstitialDidLoadAd;
    AppodealInterstitialDelegateInstance.interstitialDidFailToLoadAdDelegate = interstitialDidFailToLoadAd;
    AppodealInterstitialDelegateInstance.interstitialDidClickDelegate = interstitialDidClick;
    AppodealInterstitialDelegateInstance.interstitialDidDismissDelegate = interstitialDidDismiss;
    AppodealInterstitialDelegateInstance.interstitialWillPresentDelegate = interstitialWillPresent;
    
    [Appodeal setInterstitialDelegate:AppodealInterstitialDelegateInstance];
}


static AppodealBannerDelegate *AppodealBannerDelegateInstance;

void AppodealSetBannerDelegate(AppodealNativeDelegate bannerDidLoadAd,
                               AppodealNativeDelegate bannerDidFailToLoadAd,
                               AppodealNativeDelegate bannerDidClick,
                               AppodealNativeDelegate bannerDidShow) {
    
    AppodealBannerDelegateInstance = [AppodealBannerDelegate new];
    
    AppodealBannerDelegateInstance.bannerDidLoadAdDelegate = bannerDidLoadAd;
    AppodealBannerDelegateInstance.bannerDidFailToLoadAdDelegate = bannerDidFailToLoadAd;
    AppodealBannerDelegateInstance.bannerDidClickDelegate = bannerDidClick;
    AppodealBannerDelegateInstance.bannerDidShowDelegate = bannerDidShow;
    
    [Appodeal setBannerDelegate:AppodealBannerDelegateInstance];
}

static AppodealVideoDelegate *AppodealVideoDelegateInstance;

void AppodealSetVideoDelegate(AppodealNativeDelegate videoDidLoadAd,
                              AppodealNativeDelegate videoDidFailToLoadAd,
                              AppodealNativeDelegate videoWillDismiss,
                              AppodealNativeDelegate videoDidFinish,
                              AppodealNativeDelegate videoDidPresent) {
    
    AppodealVideoDelegateInstance = [AppodealVideoDelegate new];
    
    AppodealVideoDelegateInstance.videoDidLoadAdDelegate = videoDidLoadAd;
    AppodealVideoDelegateInstance.videoDidFailToLoadAdDelegate = videoDidFailToLoadAd;
    AppodealVideoDelegateInstance.videoWillDismissDelegate = videoWillDismiss;
    AppodealVideoDelegateInstance.videoDidFinishDelegate = videoDidFinish;
    AppodealVideoDelegateInstance.videoDidPresentDelegate = videoDidPresent;
    
    [Appodeal setVideoDelegate:AppodealVideoDelegateInstance];
}

static AppodealRewardedVideoDelegate *AppodealRewardedVideoDelegateInstance;

void AppodealSetRewardedVideoDelegate(AppodealNativeDelegate rewardedVideoDidLoadAd,
                                      AppodealNativeDelegate rewardedVideoDidFailToLoadAd,
                                      AppodealNativeDelegate rewardedVideoWillDismiss,
                                      AppodealRewardedVideoDidFinishDelegate rewardedVideoDidFinish,
                                      AppodealNativeDelegate rewardedVideoDidPresent) {
    
    AppodealRewardedVideoDelegateInstance = [AppodealRewardedVideoDelegate new];
    
    AppodealRewardedVideoDelegateInstance.rewardedVideoDidLoadAdDelegate = rewardedVideoDidLoadAd;
    AppodealRewardedVideoDelegateInstance.rewardedVideoDidFailToLoadAdDelegate = rewardedVideoDidFailToLoadAd;
    AppodealRewardedVideoDelegateInstance.rewardedVideoWillDismissDelegate = rewardedVideoWillDismiss;
    AppodealRewardedVideoDelegateInstance.rewardedVideoDidFinishDelegate = rewardedVideoDidFinish;
    AppodealRewardedVideoDelegateInstance.rewardedVideoDidPresentDelegate = rewardedVideoDidPresent;
    
    [Appodeal setRewardedVideoDelegate:AppodealRewardedVideoDelegateInstance];
}

char * AppodealGetVersion() {
    return AppodealUTF8StringFromString([Appodeal getVersion]);
}

void AppodealDisableNetwork(const char * networkName) {
    [Appodeal disableNetworkForAdType:AppodealAdTypeAll name:AppodealStringFromUTF8String(networkName)];
}

void AppodealDisableNetworkForAdTypes(const char * networkName, int adTypes) {
    [Appodeal disableNetworkForAdType:adTypes name:AppodealStringFromUTF8String(networkName)];
}

void AppodealDisableLocationPermissionCheck() {
    [Appodeal disableLocationPermissionCheck];
}

void AppodealSetDebugEnabled(BOOL debugEnabled) {
    [Appodeal setDebugEnabled:debugEnabled];
}

#pragma mark - User Settings

void AppodealSetUserAge(int age) {
    [Appodeal setUserAge:age];
}

void AppodealSetUserBirthday(const char *birthday) {
    NSDate *date = [DateFormatter() dateFromString:AppodealStringFromUTF8String(birthday)];
    if (date) {
        [Appodeal setUserBirthday:date];
    }
}

void AppodealSetUserId(const char * userId) {
    [Appodeal setUserId:AppodealStringFromUTF8String(userId)];
}

void AppodealSetUserEmail(const char * email) {
    [Appodeal setUserEmail:AppodealStringFromUTF8String(email)];
}

void AppodealSetUserFacebookId(const char * facebookId) {
    [Appodeal setUserFacebookId:AppodealStringFromUTF8String(facebookId)];
}

void AppodealSetUserVkId(const char * vkId) {
    [Appodeal setUserVkId:AppodealStringFromUTF8String(vkId)];
}

void AppodealSetUserGender(int gender) {
    [Appodeal setUserGender:gender];
}

void AppodealSetUserInterests(const char * interests) {
    [Appodeal setUserInterests:AppodealStringFromUTF8String(interests)];
}

void AppodealSetUserOccupation(int occupation) {
    [Appodeal setUserOccupation:occupation];
}

void AppodealSetUserRelationship(int relationship) {
    [Appodeal setUserRelationship:relationship];
}

void AppodealSetUserAlcoholAttitude(int attitude) {
    [Appodeal setUserAlcoholAttitude:attitude];
}

void AppodealSetUserSmokingAttitude(int attitude) {
    [Appodeal setUserSmokingAttitude:attitude];
}


