//
//  AppodealVideoDelegate.h
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 8/17/15.
//
//

#import <Foundation/Foundation.h>
#import <Appodeal/AppodealVideoDelegate.h>

#import "AppodealObjCBridge.h"

@interface AppodealVideoDelegate : NSObject <AppodealVideoDelegate>

APPODEAL_DELEGATE_PROPERTY(videoDidLoadAd)
APPODEAL_DELEGATE_PROPERTY(videoDidFailToLoadAd)
APPODEAL_DELEGATE_PROPERTY(videoWillDismiss)
APPODEAL_DELEGATE_PROPERTY(videoDidFinish)
APPODEAL_DELEGATE_PROPERTY(videoDidPresent)

@end
