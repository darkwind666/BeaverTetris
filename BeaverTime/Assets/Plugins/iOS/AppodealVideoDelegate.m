//
//  AppodealVideoDelegate.m
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 8/17/15.
//
//

#import "AppodealVideoDelegate.h"

@implementation AppodealVideoDelegate

APPODEAL_DELEGATE_METHOD(videoDidLoadAd)
APPODEAL_DELEGATE_METHOD(videoDidFailToLoadAd)
APPODEAL_DELEGATE_METHOD(videoWillDismiss)
APPODEAL_DELEGATE_METHOD(videoDidFinish)
APPODEAL_DELEGATE_METHOD(videoDidPresent)

@end
