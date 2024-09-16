#if defined(DM_PLATFORM_ANDROID)

#include <jni.h>
#include <dmsdk/dlib/android.h>

#include "../def_usercentrics.h"
#include "../usercentrics_callback_private.h"
#include "com_defold_usercentrics_UsercentricsJNI.h"
#include "usercentrics_jni.h"


JNIEXPORT void JNICALL Java_com_defold_usercentrics_UsercentricsJNI_jniAddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmUsercentrics::AddToQueueCallback((dmUsercentrics::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

namespace dmUsercentrics {

    struct Usercentrics
    {
        jobject         m_UsercentricsJNI;

        jmethodID       m_SetSettingsId;
        jmethodID       m_SetRuleSetId;
        jmethodID       m_SetConsentMediation;
        jmethodID       m_SetDefaultLanguage;
        jmethodID       m_SetInitTimeoutMillis;
        jmethodID       m_SetTimeoutMillis;
        jmethodID       m_SetVersion;
        jmethodID       m_SetNetworkMode;
        jmethodID       m_SetLoggerLevel;
        jmethodID       m_Initialize;
        jmethodID       m_ShowBanner;
    };

    static Usercentrics       g_usercentrics;

    static void CallVoidMethod(jobject instance, jmethodID method)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        env->CallVoidMethod(instance, method);
    }

    static void CallVoidMethodBool(jobject instance, jmethodID method, bool cbool)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        env->CallVoidMethod(instance, method, cbool);
    }

    static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        jstring jstr = NULL;
        if (cstr)
        {
            jstr = env->NewStringUTF(cstr);
        }

        env->CallVoidMethod(instance, method, jstr);

        if (cstr)
        {
            env->DeleteLocalRef(jstr);
        }
    }


    static void CallVoidMethodInt(jobject instance, jmethodID method, int cint)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        env->CallVoidMethod(instance, method, cint);
    }

    static void CallVoidMethodLong(jobject instance, jmethodID method, long clong)
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();

        env->CallVoidMethod(instance, method, (jlong)clong);
    }


    static void InitJNIMethods(JNIEnv* env, jclass cls)
    {
        g_usercentrics.m_SetSettingsId = env->GetMethodID(cls, "setSettingsId", "(Ljava/lang/String;)V");
        g_usercentrics.m_SetRuleSetId = env->GetMethodID(cls, "setRuleSetId", "(Ljava/lang/String;)V");
        g_usercentrics.m_SetDefaultLanguage = env->GetMethodID(cls, "setDefaultLanguage", "(Ljava/lang/String;)V");
        g_usercentrics.m_SetVersion = env->GetMethodID(cls, "setVersion", "(Ljava/lang/String;)V");

        g_usercentrics.m_Initialize = env->GetMethodID(cls, "initialize", "()V");

        g_usercentrics.m_SetInitTimeoutMillis = env->GetMethodID(cls, "setInitTimeoutMillis", "(J)V");
        g_usercentrics.m_SetTimeoutMillis = env->GetMethodID(cls, "setTimeoutMillis", "(J)V");

        g_usercentrics.m_ShowBanner = env->GetMethodID(cls, "showBanner", "(I)V");
        g_usercentrics.m_SetNetworkMode = env->GetMethodID(cls, "setNetworkMode", "(I)V");
        g_usercentrics.m_SetLoggerLevel = env->GetMethodID(cls, "setLoggerLevel", "(I)V");

        g_usercentrics.m_SetConsentMediation = env->GetMethodID(cls, "setConsentMediation", "(Z)V");

    
    }

    void Initialize_Ext()
    {
        dmAndroid::ThreadAttacher threadAttacher;
        JNIEnv* env = threadAttacher.GetEnv();
        jclass cls = dmAndroid::LoadClass(env, "com/defold/usercentrics/UsercentricsJNI");
        
        InitJNIMethods(env, cls);

        jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");

        g_usercentrics.m_UsercentricsJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));
    }

    void SetSettingsId(const char* settingsId) {
        CallVoidMethodChar(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetSettingsId, settingsId);
    }

    void SetRuleSetId(const char* rulesetID) {
        CallVoidMethodChar(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetRuleSetId, rulesetID);
    }

    void SetDefaultLanguage(const char* language) {
        CallVoidMethodChar(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetDefaultLanguage, language);
    }

    void SetVersion(const char* version) {
        CallVoidMethodChar(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetVersion, version);
    }

    void SetConsentMediation(bool value) { 
        CallVoidMethodBool(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetConsentMediation, value);
    }

    void SetInitTimeoutMillis(long millis) { 
        CallVoidMethodLong(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetInitTimeoutMillis, millis);
    }
    void SetTimeoutMillis(long millis) { 
        CallVoidMethodLong(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetTimeoutMillis, millis);
    }

    void SetNetworkMode(int mode) {
        CallVoidMethodInt(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetNetworkMode, mode);
    }

    void SetLoggerLevel(int level) {
        CallVoidMethodInt(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_SetLoggerLevel, level);
    }

    void ShowBanner(int layer) {
        CallVoidMethodInt(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_ShowBanner, layer);
    }


    void Initialize() { 
        CallVoidMethod(g_usercentrics.m_UsercentricsJNI, g_usercentrics.m_Initialize);
    }

}

#endif
