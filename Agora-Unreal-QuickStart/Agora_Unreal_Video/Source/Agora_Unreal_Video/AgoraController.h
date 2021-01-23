// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AgoraRtcEngine.h"
#include "UVideoTextureObserver.h"

class UVideoViewUserWidget;
/**
 * 
 */
class AGORA_UNREAL_VIDEO_API AgoraController : public agora::rtc::IRtcEngineEventHandler, public agora::rtc::ue4::UVideoTextureObserver
{
public:
	AgoraController();
	~AgoraController();
    
    void OnTick();

    void InitEngine(const char* appId);
    
    void ReleaseEngine();
    
    void JoinChannel();
    
    void LeaveChannel();
    
    void onWarning(int warn, const char* msg) override;

    void onError(int err, const char* msg) override;
    
    void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;

    void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;
    
    void onLeaveChannel(const agora::rtc::RtcStats& stats) override;
    
    void onUserJoined(agora::rtc::uid_t uid, int elapsed) override;

    void onUserOffline(agora::rtc::uid_t uid, agora::rtc::USER_OFFLINE_REASON_TYPE reason) override;
    
    void OnLocalVideoTextureUpdate(agora::rtc::ue4::VideoTextureFrame& _videoFrame) override;

    void OnRemoteVideoTextureUpdate(unsigned int uid, agora::rtc::ue4::VideoTextureFrame& _videoFrame) override;
    
    void OnVideoRenderStop() override;
    
    void SetVideoViewWidget(UVideoViewUserWidget* videoWidget);
    
private:
    agora::rtc::ue4::AgoraRtcEngine* _rtcEnginePtr = nullptr;
    
    UVideoViewUserWidget* _videoWidget = nullptr;
};
