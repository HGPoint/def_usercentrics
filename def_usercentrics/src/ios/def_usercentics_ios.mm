#if defined(DM_PLATFORM_IOS)

#include "../def_usercentrics.h"
#include "../usercentrics_callback_private.h"

#import "usercentricsbridge/usercentricsbridge-Swift.h"

namespace dmUsercentrics {

    UserCentricsBridge *bridge;

    void Initialize_Ext(){
        bridge = [[UserCentricsBridge alloc] init];
    }

    void SetSettingsId(const char* settingsId){
        [bridge setSettingsId:[NSString stringWithUTF8String:settingsId]];
    }
    void SetRuleSetId(const char* rulesetID){
        [bridge setRuleSetId:[NSString stringWithUTF8String:rulesetID]];
    }
    void SetDefaultLanguage(const char* language){
        [bridge setDefaultLanguage:[NSString stringWithUTF8String:language]];
    }
    void SetVersion(const char* version){
        [bridge setVersion:[NSString stringWithUTF8String:version]];
    }

    void SetConsentMediation(bool value){
        [bridge setConsentMediation:value];
    }
    void SetInitTimeoutMillis(long millis){
        [bridge setInitTimeoutMillis:millis];
    }
    void SetTimeoutMillis(long millis){
        [bridge setTimeoutMillis:millis];
    }
    void SetNetworkMode(int mode){
        [bridge setNetworkMode: mode];
    }
    void SetLoggerLevel(int level){
        [bridge setLoggerLevel: level];
    }
    
    void Initialize(){
        [bridge initUsercentricsWithCallback:^(NSString *userResponse) {
            const char *JsonCString = [userResponse UTF8String];
            AddToQueueCallback(USERCENTRICS_READY_MSG, JsonCString);
        }];
    }

    void ShowBanner(int layer){
        [bridge showBanner:layer :^(NSString * userResponse) {
            const char *JsonCString = [userResponse UTF8String];
            AddToQueueCallback(USERCENTRICS_BANNER_SHOWN_MSG, JsonCString);
        }];
    }
}
#endif