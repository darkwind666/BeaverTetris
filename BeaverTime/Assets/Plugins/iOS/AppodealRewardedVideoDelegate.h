//
//  AppodealRewardedVideoDelegate.h
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 11/17/15.
//
//

#import <Foundation/Foundation.h>
#import <Appodeal/AppodealRewardedVideoDelegate.h>

#import "AppodealObjCBridge.h"

typedef void (*AppodealRewardedVideoDidFinishDelegate) (int, const char *);

@interface AppodealRewardedVideoDelegate : NSObject <AppodealRewardedVideoDelegate>

APPODEAL_DELEGATE_PROPERTY(rewardedVideoDidLoadAd)
APPODEAL_DELEGATE_PROPERTY(rewardedVideoDidFailToLoadAd)
APPODEAL_DELEGATE_PROPERTY(rewardedVideoWillDismiss)
APPODEAL_DELEGATE_PROPERTY(rewardedVideoDidPresent)

@property (assign, nonatomic) AppodealRewardedVideoDidFinishDelegate rewardedVideoDidFinishDelegate;

@end
