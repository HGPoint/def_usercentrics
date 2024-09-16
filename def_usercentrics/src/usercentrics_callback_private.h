#pragma once

#include "def_usercentrics.h"
#include <dmsdk/sdk.h>

namespace dmUsercentrics {

struct CallbackData
{
    MessageId msg;
    char* json;
};

void SetLuaCallback(lua_State* L, int pos);
void UpdateCallback();
void InitializeCallback();
void FinalizeCallback();

void AddToQueueCallback(MessageId type, const char*json);

} //namespace dmUsercentrics
