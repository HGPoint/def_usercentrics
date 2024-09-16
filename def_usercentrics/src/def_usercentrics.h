#pragma once
#if defined(DM_PLATFORM_IOS) || defined(DM_PLATFORM_ANDROID)

namespace dmUsercentrics {

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
        USERCENTRICS_BANNER_SHOWN_MSG = 2
    };

    void Initialize_Ext();

    void SetSettingsId(const char* settingsId);
    void SetRuleSetId(const char* rulesetID);
    void SetConsentMediation(bool value);
    void SetDefaultLanguage(const char* language);
    void SetInitTimeoutMillis(long millis);
    void SetTimeoutMillis(long millis);
    void SetVersion(const char* version);
    void SetNetworkMode(int mode);
    void SetLoggerLevel(int level);
    void Initialize();
    void ShowBanner(int layer);
}
#endif