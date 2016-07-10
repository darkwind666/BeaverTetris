//
//  AppodealInterstitialDelegate.m
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 8/17/15.
//
//

#import "AppodealInterstitialDelegate.h"

@implementation AppodealInterstitialDelegate

APPODEAL_DELEGATE_METHOD(interstitialDidLoadAd)
APPODEAL_DELEGATE_METHOD(interstitialDidFailToLoadAd)
APPODEAL_DELEGATE_METHOD(interstitialWillPresent)
APPODEAL_DELEGATE_METHOD(interstitialDidDismiss)
APPODEAL_DELEGATE_METHOD(interstitialDidClick)

@end
