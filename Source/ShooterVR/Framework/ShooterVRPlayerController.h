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

//���ֱ�����
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

//���ֱ��ֱ�����
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
	//����
protected:
	//���ڿ�ǹ or UIѡ��
	void TriggerLeft(const FInputActionValue& InInputValue);

	//��ɫ������ת��
	void TriggerLeftTrackpakL(const FInputActionValue& InInputValue);
	void TriggerLeftTrackpakR(const FInputActionValue& InInputValue);

	//��ɫ�ƶ�
	void TriggerLeftTrackpakUPStart(const FInputActionValue& InInputValue);
	void TriggerLeftTrackpakUPEnd(const FInputActionValue& InInputValue);

	//��
	void TriggerLeftTrackpakD(const FInputActionValue& InInputValue);

	//ץȡ
	void GrabLeftStart(const FInputActionValue& InInputValue);
	void GrabLeftEnd(const FInputActionValue& InInputValue);

	//�ռ���ק
	void MenuLeftStart(const FInputActionValue& InInputValue);
	void MenuLeftEnd(const FInputActionValue& InInputValue);

	//��������
protected:
	//���ڿ�ǹ or UIѡ��
	void TriggerRight(const FInputActionValue& InInputValue);

	//��ɫ������ת��
	void TriggerRightTrackpakL(const FInputActionValue& InInputValue);
	void TriggerRightTrackpakR(const FInputActionValue& InInputValue);

	//��ɫ˲���ƶ�
	void TriggerRightTrackpakUPStart(const FInputActionValue& InInputValue);
	void TriggerRightTrackpakUPEnd(const FInputActionValue& InInputValue);

	//ץȡ
	void GrabRightStart(const FInputActionValue& InInputValue);
	void GrabRightEnd(const FInputActionValue& InInputValue);

	//
	void MenuRightStart(const FInputActionValue& InInputValue);
	void MenuRightEnd(const FInputActionValue& InInputValue);

public:
	void AddInputMappingContext(TObjectPtr<UInputMappingContext> InInputMappingContext,int32 Priority = 100);
	void RemoveInputMappingContext(TObjectPtr<UInputMappingContext> InInputMappingContext);
};
