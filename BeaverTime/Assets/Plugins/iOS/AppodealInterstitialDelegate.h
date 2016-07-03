//
//  AppodealInterstitialDelegate.h
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 8/17/15.
//
//

#import <Foundation/Foundation.h>
#import <Appodeal/AppodealInterstitialDelegate.h>

#import "AppodealObjCBridge.h"

@interface AppodealInterstitialDelegate : NSObject <AppodealInterstitialDelegate>

APPODEAL_DELEGATE_PROPERTY(interstitialDidLoadAd)
APPODEAL_DELEGATE_PROPERTY(interstitialDidFailToLoadAd)
APPODEAL_DELEGATE_PROPERTY(interstitialWillPresent)
APPODEAL_DELEGATE_PROPERTY(interstitialDidDismiss)
APPODEAL_DELEGATE_PROPERTY(interstitialDidClick)

@end