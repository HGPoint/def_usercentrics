//
//  def_usercentrics_ios.m
//  test_usercmp
//
//  Created by Salavat Rakhmanov on 13/9/24.
//

#import <Usercentrics/Usercentrics.h>
#import <UsercentricsUI/UsercentricsUI-Swift.h>
#import <Foundation/NSJSONSerialization.h>

#import "usercentricsbridge/usercentricsbridge-Swift.h"
////////////////////////////
enum BannerLayer
{
    FIRST_LAYER = 1,
    SECOND_LAYER = 2
};

enum NetworkMode
{
    NETWORK_MODE_WORLD = 1,
    NETWORK_MODE_EU = 2
};

enum LogLevel
{
    LOG_LEVEL_NONE = 1,
    LOG_LEVEL_ERROR = 2,
    LOG_LEVEL_WARNING = 3,
    LOG_LEVEL_DEBUG = 4,
};

enum MessageId
{
    USERCENTRICS_READY_MSG = 1,
    USERCENTRICS_READY_ERROR_MSG = 2,
    USERCENTRICS_BANNER_SHOWN_MSG = 3
};



void AddToQueueCallback(enum MessageId type, const char*json)
{
}

//////////////

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
