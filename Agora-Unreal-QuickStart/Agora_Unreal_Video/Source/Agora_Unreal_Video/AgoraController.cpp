// Copyright (c) 2019 Agora.io. All rights reserved.


#include "AgoraController.h"
#include "VideoViewUserWidget.h"

using namespace agora::rtc;
using namespace agora::rtc::ue4;

AgoraController::AgoraController():_rtcEnginePtr(nullptr)
{
    
}

AgoraController::~AgoraController()
{
    ReleaseEngine();
}

void AgoraController::OnTick() {
    _rtcEnginePtr->OnTick();
}

void AgoraController::InitEngine(const char* appId) {
    _rtcEnginePtr = AgoraRtcEngine::createAgoraRtcEngine();
    RtcEngineContext _rtcEngineContext;
    _rtcEngineContext.appId = appId;
    _rtcEngineContext.eventHandler = this;
    _rtcEnginePtr->initialize(_rtcEngineContext);
}

void AgoraController::ReleaseEngine() {
    _rtcEnginePtr->release();
    _rtcEnginePtr = nullptr;
}

void AgoraController::JoinChannel() {
    _rtcEnginePtr->setChannelProfile(CHANNEL_PROFILE_TYPE::CHANNEL_PROFILE_COMMUNICATION);
    _rtcEnginePtr->enableAudio();
    _rtcEnginePtr->enableVideo();
    _rtcEnginePtr->registerVideoFrameObserver(this);
    auto ret = _rtcEnginePtr->joinChannel("", "Hello_Agora", "", 0);
    UE_LOG(LogTemp, Warning, TEXT("JoinChannel ret: %d"), ret);
}

void AgoraController::LeaveChannel() {
    _rtcEnginePtr->leaveChannel();
    _rtcEnginePtr->registerVideoFrameObserver(nullptr);
}

void AgoraController::onWarning(int warn, const char* msg) {
    UE_LOG(LogTemp, Warning, TEXT("onWarning warn: %d"), warn);
}

void AgoraController::onError(int err, const char* msg) {
    UE_LOG(LogTemp, Warning, TEXT("onError err: %d, msg: %s"), err, msg);
}

void AgoraController::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
    UE_LOG(LogTemp, Warning, TEXT("onJoinChannelSuccess channel: %s, uid: %u"), channel, uid);
}

void AgoraController::onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
    UE_LOG(LogTemp, Warning, TEXT("onRejoinChannelSuccess channel"));
}

void AgoraController::onLeaveChannel(const RtcStats& stats) {
    UE_LOG(LogTemp, Warning, TEXT("onLeaveChannel"));
}

void AgoraController::onUserJoined(uid_t uid, int elapsed) {
    UE_LOG(LogTemp, Warning, TEXT("onUserJoined  uid: %u"), uid);
}

void AgoraController::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
    UE_LOG(LogTemp, Warning, TEXT("onUserOffline  uid: %u"), uid);
}

void AgoraController::OnLocalVideoTextureUpdate(VideoTextureFrame& _videoFrame) {
    UE_LOG(LogTemp, Warning, TEXT("OnLocalVideoTextureUpdate uid"));
    if (_videoWidget) {
        _videoWidget->OnLocalVideoTextureUpdate(_videoFrame);
    }
}

void AgoraController::OnRemoteVideoTextureUpdate(unsigned int uid, VideoTextureFrame& _videoFrame) {
    UE_LOG(LogTemp, Warning, TEXT("OnRemoteVideoTextureUpdate uid: %u"), uid);
    if (_videoWidget) {
        _videoWidget->OnRemoteVideoTextureUpdate(uid, _videoFrame);
    }
}

void AgoraController::OnVideoRenderStop() {
    
}

void AgoraController::SetVideoViewWidget(UVideoViewUserWidget* videoWidget) {
    _videoWidget = videoWidget;
}
