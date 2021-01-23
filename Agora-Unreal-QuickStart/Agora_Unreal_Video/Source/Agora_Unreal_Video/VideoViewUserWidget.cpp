// Fill out your copyright notice in the Description page of Project Settings.


#include "VideoViewUserWidget.h"
#include "AgoraController.h"

void UVideoViewUserWidget::NativeConstruct() {
    Super::NativeConstruct();
    _agoraControllerPtr = new AgoraController();
    _agoraControllerPtr->InitEngine("5db0d12c40354100abd7a8a0adaa1fb8");
    _agoraControllerPtr->SetVideoViewWidget(this);
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget ====== NativeConstruct ======"));
    JoinBtn->OnClicked.AddDynamic(this, &UVideoViewUserWidget::OnJoinButtonClick);
    LeaveBtn->OnClicked.AddDynamic(this, &UVideoViewUserWidget::OnLeaveButtonClick);
}

void UVideoViewUserWidget::NativeDestruct() {
    Super::NativeDestruct();
    delete _agoraControllerPtr;
    _agoraControllerPtr = nullptr;
}

void UVideoViewUserWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime) {
    Super::NativeTick(MyGeometry, DeltaTime);
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget ===== NativeTick ======"));
    _agoraControllerPtr->OnTick();
}

void UVideoViewUserWidget::OnLocalVideoTextureUpdate(agora::rtc::ue4::VideoTextureFrame& _videoFrame) {
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget OnLocalVideoTextureUpdate ======"));
    LocalBrush = _videoFrame.Brush;
    localVideo->SetBrush(LocalBrush);
}

void UVideoViewUserWidget::OnRemoteVideoTextureUpdate(unsigned int uid, agora::rtc::ue4::VideoTextureFrame& _videoFrame) {
    RemoteBrush = _videoFrame.Brush;
    remoteVideo->SetBrush(RemoteBrush);
}

void UVideoViewUserWidget::OnVideoRenderStop() {
    
}

void UVideoViewUserWidget::OnJoinButtonClick() {
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget OnJoinButtonClick ======"));
    _agoraControllerPtr->JoinChannel();
    SetButtonClickAble(false);
}

void UVideoViewUserWidget::OnLeaveButtonClick() {
    UE_LOG(LogTemp, Warning, TEXT("UVideoViewUserWidget OnLeaveButtonClick ======"));
    _agoraControllerPtr->LeaveChannel();
    SetButtonClickAble(true);
}

void UVideoViewUserWidget::SetButtonClickAble(bool enable) {
    JoinBtn->SetIsEnabled(enable);
    LeaveBtn->SetIsEnabled(!enable);
}
