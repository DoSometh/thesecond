// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleModularPlayerController.h"
#include "ShooterVRPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class SHOOTERVR_API AShooterVRPlayerController : public ASimpleModularPlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IMCDefaultGamepadContext;

//左手柄动作
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerLeftTrackpakL;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerLeftTrackpakR;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerLeftTrackpakUP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerLeftTrackpakD;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAGrabLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAMenuLeft;

//右手柄手柄动作
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerRightTrackpakL;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerRightTrackpakR;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerRightTrackpakUP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAGrabRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IAMenuRight;
public:
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	//Input
	//左手
protected:
	//用于开枪 or UI选择
	void TriggerLeft(const FInputActionValue& InInputValue);

	//角色的左右转动
	void TriggerLeftTrackpakL(const FInputActionValue& InInputValue);
	void TriggerLeftTrackpakR(const FInputActionValue& InInputValue);

	//角色移动
	void TriggerLeftTrackpakUPStart(const FInputActionValue& InInputValue);
	void TriggerLeftTrackpakUPEnd(const FInputActionValue& InInputValue);

	//下
	void TriggerLeftTrackpakD(const FInputActionValue& InInputValue);

	//抓取
	void GrabLeftStart(const FInputActionValue& InInputValue);
	void GrabLeftEnd(const FInputActionValue& InInputValue);

	//空间拖拽
	void MenuLeftStart(const FInputActionValue& InInputValue);
	void MenuLeftEnd(const FInputActionValue& InInputValue);

	//处理右手
protected:
	//用于开枪 or UI选择
	void TriggerRight(const FInputActionValue& InInputValue);

	//角色的左右转动
	void TriggerRightTrackpakL(const FInputActionValue& InInputValue);
	void TriggerRightTrackpakR(const FInputActionValue& InInputValue);

	//角色瞬间移动
	void TriggerRightTrackpakUPStart(const FInputActionValue& InInputValue);
	void TriggerRightTrackpakUPEnd(const FInputActionValue& InInputValue);

	//抓取
	void GrabRightStart(const FInputActionValue& InInputValue);
	void GrabRightEnd(const FInputActionValue& InInputValue);

	//
	void MenuRightStart(const FInputActionValue& InInputValue);
	void MenuRightEnd(const FInputActionValue& InInputValue);

public:
	void AddInputMappingContext(TObjectPtr<UInputMappingContext> InInputMappingContext,int32 Priority = 100);
	void RemoveInputMappingContext(TObjectPtr<UInputMappingContext> InInputMappingContext);
};
