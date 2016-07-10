//
//  AppodealBannerDelegate.h
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 8/17/15.
//
//

#import <Foundation/Foundation.h>
#import <Appodeal/AppodealBannerDelegate.h>

#import "AppodealObjCBridge.h"

@interface AppodealBannerDelegate : NSObject <AppodealBannerDelegate>

APPODEAL_DELEGATE_PROPERTY(bannerDidLoadAd)
APPODEAL_DELEGATE_PROPERTY(bannerDidFailToLoadAd)
APPODEAL_DELEGATE_PROPERTY(bannerDidClick)
APPODEAL_DELEGATE_PROPERTY(bannerDidShow)

@end