//
//  AppodealObjCBridge.h
//  Unity-iPhone
//
//  Created by Ivan Doroshenko on 8/17/15.
//
//

FOUNDATION_EXPORT NSString *AppodealStringFromUTF8String(const char *bytes);
FOUNDATION_EXPORT char * AppodealUTF8StringFromString(NSString *string);

typedef void (*AppodealNativeDelegate) ();

#define APPODEAL_DELEGATE_PROPERTY(NAME) \
    @property (assign, nonatomic) AppodealNativeDelegate NAME ## Delegate;
    
#define APPODEAL_DELEGATE_METHOD(NAME) \
    - (void)NAME { \
        if ([self NAME ## Delegate]) { \
            [self NAME ## Delegate](); \
        } \
    }