//
//  AppodealRewardedVideoDelegate.m
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 11/17/15.
//
//

#import "AppodealRewardedVideoDelegate.h"

@implementation AppodealRewardedVideoDelegate

APPODEAL_DELEGATE_METHOD(rewardedVideoDidLoadAd)
APPODEAL_DELEGATE_METHOD(rewardedVideoDidFailToLoadAd)
APPODEAL_DELEGATE_METHOD(rewardedVideoWillDismiss)
APPODEAL_DELEGATE_METHOD(rewardedVideoDidPresent)

- (void)rewardedVideoDidFinish:(NSUInteger)rewardAmount name:(NSString *)rewardName {
    if (self.rewardedVideoDidFinishDelegate) {
        self.rewardedVideoDidFinishDelegate((int)rewardAmount, AppodealUTF8StringFromString(rewardName));
    }
}

@end
