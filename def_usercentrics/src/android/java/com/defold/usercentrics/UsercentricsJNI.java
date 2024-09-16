package com.defold.usercentrics;

import android.app.Activity;
import android.util.Log;

import com.usercentrics.sdk.*;
import com.usercentrics.sdk.models.common.NetworkMode;
import com.usercentrics.sdk.models.common.UsercentricsLoggerLevel;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

public class UsercentricsJNI {

    public static native void jniAddToQueue(int msg, String json);

    int FIRST_LAYER = 1;
    int SECOND_LAYER = 2;

    final int LOG_LEVEL_NONE = 1;
    final int LOG_LEVEL_ERROR = 2;
    final int LOG_LEVEL_WARNING = 3;
    final int LOG_LEVEL_DEBUG = 4;


    final int NETWORK_MODE_WORLD = 1;
    final int NETWORK_MODE_EU = 2;

    final int USERCENTRICS_READY_MSG = 1;
    final int USERCENTRICS_BANNER_SHOWN_MSG = 2;

    Activity mActivity;
    UsercentricsOptions options = new UsercentricsOptions();

    public UsercentricsJNI(final Activity activity) {
        mActivity = activity;
    }

    public void setSettingsId(String settingsId) {
        options.setSettingsId(settingsId);
    }

    public void setRuleSetId(String rulesetID) {
        options.setRuleSetId(rulesetID);
    }

    public void setConsentMediation(boolean value) {
        options.setConsentMediation(value);
    }

    public void setDefaultLanguage(String language) {
        options.setDefaultLanguage(language);
    }

    public void setInitTimeoutMillis(long millis) {
        options.setInitTimeoutMillis(millis);
    }

    public void setTimeoutMillis(long millis) {
        options.setTimeoutMillis(millis);
    }

    public void setVersion(String version) {
        options.setVersion(version);
    }

    public void setNetworkMode(int mode) {
        switch (mode) {
            case NETWORK_MODE_EU:
                options.setNetworkMode(NetworkMode.EU);
                break;
            default:
                options.setNetworkMode(NetworkMode.WORLD);
        }
    }

    public void setLoggerLevel(int level) {
        switch (level) {
            case LOG_LEVEL_NONE:
                options.setLoggerLevel(UsercentricsLoggerLevel.NONE);
                break;
            case LOG_LEVEL_DEBUG:
                options.setLoggerLevel(UsercentricsLoggerLevel.DEBUG);
                break;
            case LOG_LEVEL_WARNING:
                options.setLoggerLevel(UsercentricsLoggerLevel.WARNING);
                break;
            case LOG_LEVEL_ERROR:
                options.setLoggerLevel(UsercentricsLoggerLevel.ERROR);
                break;
            default:
                options.setLoggerLevel(UsercentricsLoggerLevel.ERROR);
                break;
        }
    }

    // https://www.baeldung.com/java-json-escaping
    private String getJsonConversionErrorMessage(String messageText) {
        String message;
        try {
            JSONObject obj = new JSONObject();
            obj.put("error", messageText);
            message = obj.toString();
        } catch (JSONException e) {
            message = "{ \"error\": \"Error while converting simple message to JSON.\" }";
        }
        return message;
    }

    private JSONArray getServiceConsentsJson(List<UsercentricsServiceConsent> consents) {
        JSONArray array = new JSONArray();
        try {
            for (UsercentricsServiceConsent consent : consents) {
                JSONObject objConsent = new JSONObject();
                objConsent.put("dataProcessor", consent.getDataProcessor());
                objConsent.put("status", consent.getStatus());
                objConsent.put("type", consent.getType());
                objConsent.put("templateId", consent.getTemplateId());

                JSONArray histArray = new JSONArray();
                for (UsercentricsConsentHistoryEntry history : consent.getHistory()) {
                    JSONObject objHistory = new JSONObject();
                    objHistory.put("status", history.getStatus());
                    objHistory.put("timestampInMillis", history.getTimestampInMillis());
                    history.getStatus();
                }
                objConsent.put("history", histArray);
                array.put(objConsent);
            }
        } catch (JSONException e) {

        }
        return array;
    }

    public void initialize() {
        Usercentrics.isReady(status -> {
                    String message = "";
                    try {
                        JSONObject obj = new JSONObject();
                        obj.put("shouldCollectConsent", status.getShouldCollectConsent());
                        obj.put("consents", getServiceConsentsJson(status.getConsents()));
                        message = obj.toString();
                    } catch (JSONException e) {
                        message = getJsonConversionErrorMessage(e.getMessage());
                    }
                    jniAddToQueue(USERCENTRICS_READY_MSG, message);
                    return null;
                }, error -> {
                    jniAddToQueue(USERCENTRICS_READY_MSG, getJsonConversionErrorMessage(error.getMessage()));
                    return null;
                }
        );
        Usercentrics.initialize(mActivity, options);
    }

    public kotlin.Unit bannerCB(UsercentricsConsentUserResponse userResponse) {
        String message = "";
        try {
            JSONObject obj = new JSONObject();
            obj.put("controllerId", userResponse.getControllerId());
            obj.put("consents", getServiceConsentsJson(userResponse.getConsents()));
            userResponse.getConsents();
            message = obj.toString();
        } catch (JSONException e) {
            message = getJsonConversionErrorMessage(e.getMessage());
        }
        jniAddToQueue(USERCENTRICS_BANNER_SHOWN_MSG, message);
        return null;
    }

    public void showBanner(int layer) {
        UsercentricsBanner banner = new UsercentricsBanner(mActivity, null);
        if (layer == FIRST_LAYER) {
            banner.showFirstLayer(userResponse -> bannerCB(userResponse));
        } else if (layer == SECOND_LAYER) {
            banner.showSecondLayer(userResponse -> bannerCB(userResponse));
        }
    }
}