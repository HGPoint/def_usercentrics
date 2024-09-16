#define EXTENSION_NAME DefUsercentrics
#define LIB_NAME "DefUsercentrics"
#define MODULE_NAME "usercentrics"
#define DLIB_LOG_DOMAIN LIB_NAME

#include <dmsdk/sdk.h>

// Import the SDK header on other platforms

#include "def_usercentrics.h"
#include "utils/LuaUtils.h"
#include "usercentrics_callback_private.h"


namespace dmUsercentrics {

// setSettingsId(String settingsId)
// setRuleSetId(String rulesetID)
// setConsentMediation(boolean value)
// setDefaultLanguage(String language)
// setInitTimeoutMillis(long millis)
// setTimeoutMillis(long millis)
// setVersion(String version)
// setNetworkMode(int mode)
// setLoggerLevel(int level)
// initialize()
// showBanner(int layer)


static int Lua_SetCallback(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);
    SetLuaCallback(L, 1);
    return 0;
}

static int Lua_SetSettingsId(lua_State* L) {  
    DM_LUA_STACK_CHECK(L, 0);    
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* param = luaL_checkstring(L, 1);
    SetSettingsId(param); 
    return 0; 
}

static int Lua_SetRuleSetId(lua_State* L) {  
    DM_LUA_STACK_CHECK(L, 0);    
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* param = luaL_checkstring(L, 1);
    SetRuleSetId(param); 
    return 0; 
}

static int Lua_SetDefaultLanguage(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);    
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* param = luaL_checkstring(L, 1);
    SetDefaultLanguage(param); 
    return 0; 
}

static int Lua_SetVersion(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);    
    if (lua_type(L, 1) != LUA_TSTRING) {
        char msg[256];
        snprintf(msg, sizeof(msg), "Expected string, got %s. Wrong type for Rewarded UnitId variable '%s'.", luaL_typename(L, 1), lua_tostring(L, 1));
        luaL_error(L, msg);
        return 0;
    }
    const char* param = luaL_checkstring(L, 1);
    SetVersion(param); 
    return 0; 
}

static int Lua_SetConsentMediation(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);    
    bool param = luaL_checkbool(L, 1);
    SetConsentMediation(param); 
    return 0; 
}

static int Lua_SetInitTimeoutMillis(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);
    long param = luaL_checklong(L, 1);
    SetInitTimeoutMillis(param); 
    return 0; 
}

static int Lua_SetTimeoutMillis(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);
    long param = luaL_checklong(L, 1);
    SetTimeoutMillis(param); 
    return 0; 
}

static int Lua_SetNetworkMode(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);
    int param = luaL_checkinteger(L, 1);
    SetNetworkMode(param); return 0; 
}

static int Lua_SetLoggerLevel(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);
    int param = luaL_checkinteger(L, 1);
    SetLoggerLevel(param); return 0; 
}

static int Lua_Initialize(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);
    Initialize(); 
    return 0; 
}

static int Lua_ShowBanner(lua_State* L) { 
    DM_LUA_STACK_CHECK(L, 0);
    int param = luaL_checkinteger(L, 1);
    ShowBanner(param); 
    return 0; 
}

static const luaL_reg Module_methods[] =
{
    {"set_settings_id", Lua_SetSettingsId},
    {"set_ruleset_id", Lua_SetRuleSetId},
    {"set_consent_mediation", Lua_SetConsentMediation},
    {"set_default_language", Lua_SetDefaultLanguage},
    {"set_init_timeout_millis", Lua_SetInitTimeoutMillis},
    {"set_timeout_millis", Lua_SetTimeoutMillis},
    {"set_version", Lua_SetVersion},
    {"set_network_mode", Lua_SetNetworkMode},
    {"set_logger_level", Lua_SetLoggerLevel},
    {"initialize", Lua_Initialize},
    {"show_banner", Lua_ShowBanner},
    {"set_callback", Lua_SetCallback},
    {0, 0}
};

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);

     #define SETCONSTANT(name) \
    lua_pushnumber(L, (lua_Number) name); \
    lua_setfield(L, -2, #name); \

    SETCONSTANT(FIRST_LAYER)
    SETCONSTANT(SECOND_LAYER)

    SETCONSTANT(NETWORK_MODE_WORLD)
    SETCONSTANT(NETWORK_MODE_EU)

    SETCONSTANT(LOG_LEVEL_NONE)
    SETCONSTANT(LOG_LEVEL_ERROR)
    SETCONSTANT(LOG_LEVEL_WARNING)
    SETCONSTANT(LOG_LEVEL_DEBUG)

    SETCONSTANT(USERCENTRICS_READY_MSG)
    SETCONSTANT(USERCENTRICS_BANNER_SHOWN_MSG)


    #undef SETCONSTANT
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

dmExtension::Result InitializeDefUsercentrics(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    dmLogInfo("Registered extension DefUsercentrics");
    Initialize_Ext();
    InitializeCallback();
   
    return dmExtension::RESULT_OK;
}

static dmExtension::Result UpdateDefUsercentrics(dmExtension::Params* params)
{
    UpdateCallback();
    return dmExtension::RESULT_OK;
}


static dmExtension::Result FinalizeAppLovinMax(dmExtension::Params* params)
{
    FinalizeCallback();
    return dmExtension::RESULT_OK;
}


DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, 0, 0, InitializeDefUsercentrics, UpdateDefUsercentrics, 0, FinalizeAppLovinMax)
    
} //namespace