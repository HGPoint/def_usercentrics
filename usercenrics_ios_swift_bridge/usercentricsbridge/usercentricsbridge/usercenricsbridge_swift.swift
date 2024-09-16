//
//  usercenricsbridge_swift.swift
//  usercentricsbridge
//
//  Created by Salavat Rakhmanov on 13/9/24.
//

import Usercentrics
import UsercentricsUI

@objc public class UserCentricsBridge: NSObject {
    @objc public var options:UsercentricsOptions = UsercentricsOptions()
    
    var FIRST_LAYER:Int = 1
    var SECOND_LAYER:Int = 2
    
    var LOG_LEVEL_NONE:Int = 1
    var LOG_LEVEL_ERROR:Int = 2
    var LOG_LEVEL_WARNING:Int = 3
    var LOG_LEVEL_DEBUG:Int = 4
    
    var NETWORK_MODE_WORLD:Int = 1
    var NETWORK_MODE_EU:Int = 2
    
    @objc public func setSettingsId(_ settingsId: String) {
            options.settingsId = settingsId
        }
        
        @objc public func setRuleSetId(_ rulesetID: String) {
            options.ruleSetId = rulesetID
        }
        
        @objc public func setDefaultLanguage(_ language: String) {
            options.defaultLanguage = language
        }
        
        @objc public func setVersion(_ version: String) {
            options.version = version
        }
        
        @objc public func setConsentMediation(_ value: Bool) {
            options.consentMediation = value
        }
        
        @objc public func setInitTimeoutMillis(_ millis: Int64) {
            options.initTimeoutMillis = millis
        }
        
        @objc public func setTimeoutMillis(_ millis: Int64) {
            options.timeoutMillis = millis
        }
        
        @objc public func setNetworkMode(_ mode: Int) {
            switch mode {
            case NETWORK_MODE_EU:
                options.networkMode = NetworkMode.eu
            default:
                options.networkMode = NetworkMode.world
            }
        }
        
        @objc public func setLoggerLevel(_ level: Int) {
            switch level {
            case LOG_LEVEL_DEBUG:
                options.loggerLevel = UsercentricsLoggerLevel.debug
            case LOG_LEVEL_WARNING:
                options.loggerLevel = UsercentricsLoggerLevel.warning
            case LOG_LEVEL_ERROR:
                options.loggerLevel = UsercentricsLoggerLevel.error
            default:
                options.loggerLevel = UsercentricsLoggerLevel.none
            }
        }
    
    @objc public func showBanner(level: Int) {
        let banner = UsercentricsBanner()
        
        switch level {
        case 1:
            banner.showFirstLayer { userResponse in
                // Handle user response for the first layer
            }
        case 2:
            banner.showSecondLayer { userResponse in
                // Handle user response for the second layer
            }
        default:
            print("Invalid banner level: \(level)")
        }
    }
    
    struct Consent:Encodable{
        var dataProcessor: String = ""
        var status: Bool = false
        var templateId: String = ""
    }
    struct StatusResponce: Encodable {
        var shouldCollectConsent: Bool?
        var consents = [Consent]()
    }
    
    @objc public func initUsercentrics(callback: @escaping (_ userResponse: String) -> Void){
        UsercentricsCore.configure(options: options)
        UsercentricsCore.isReady { [weak self] status in
            guard let self = self else { return }
            var statusResp: StatusResponce = StatusResponce()
            statusResp.shouldCollectConsent = status.shouldCollectConsent
            for consent in status.consents{
                statusResp.consents.append(Consent(dataProcessor: consent.dataProcessor, status: consent.status, templateId: consent.templateId))
            }
            var jsonString = ""
            do {
                let data = try JSONEncoder().encode(statusResp)
                jsonString = String(data: data, encoding: .utf8) ?? ""
            } catch {
                jsonString = "{ \"error\": \" " + error.localizedDescription + "\"}"
            }
            callback(jsonString)
        } onFailure: { error in
            var jsonString = "{ \"error\": \" " + error.localizedDescription + "\"}"
            callback(jsonString)
        }
    }
    
    @objc public func showBanner(_ layer:Int,_ callback: @escaping (_ userResponse: String) -> Void){
        if (layer == 1){
            let banner = UsercentricsBanner()
            banner.showFirstLayer() { userResponse in
                var statusResp: StatusResponce = StatusResponce()
                for consent in userResponse.consents{
                    statusResp.consents.append(Consent(dataProcessor: consent.dataProcessor, status: consent.status, templateId: consent.templateId))
                }
                var jsonString = ""
                do {
                    let data = try JSONEncoder().encode(statusResp)
                    jsonString = String(data: data, encoding: .utf8) ?? ""
                } catch {
                    jsonString = "{ \"error\": \" " + error.localizedDescription + "\"}"
                }
                callback(jsonString)
            }
        }
        else if(layer == 2){
            let banner = UsercentricsBanner()
            banner.showSecondLayer() { userResponse in
                var statusResp: StatusResponce = StatusResponce()
                for consent in userResponse.consents{
                    statusResp.consents.append(Consent(dataProcessor: consent.dataProcessor, status: consent.status, templateId: consent.templateId))
                }
                var jsonString = ""
                do {
                    let data = try JSONEncoder().encode(statusResp)
                    jsonString = String(data: data, encoding: .utf8) ?? ""
                } catch {
                    jsonString = "{ \"error\": \" " + error.localizedDescription + "\"}"
                }
                callback(jsonString)
            }
        }
    }
}
