// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRWeaponBase.h"
#include "../../ShooterVRType.h"
#include "VRGunBase.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class USimpleSliderComponent;
class USimpleClipComponent;
class UVRGunAttributeSet;
struct FInputBindingHandle;
class AVRClipBase;
class UArrowComponent;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class SHOOTERVR_API AVRGunBase : public AVRWeaponBase
{
	GENERATED_BODY()

	UPROPERTY(Category = Attrubute, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UVRGunAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USimpleSliderComponent> SliderTrigger;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USimpleClipComponent> ClipComponent;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UArrowComponent> BullectSpawnArrow;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IMCGunLeftGamepadContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> IMCGunRightGamepadContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerRight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "EnhancedInput|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> IATriggerLeft;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GameplayAbility", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayAbility> GameplayAbility_OpenFire;
	
	//˦
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Clip, meta = (AllowPrivateAccess = "true"))
	float SlingClipDistanceByFrame;
	
	//
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slider Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> SliderPullSoundCue;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slider Sound", meta = (AllowPrivateAccess = "true"))
	float SliderPullSoundStartTime;
	
	//
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slider Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <USoundBase> SliderSpringbackSoundCue;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slider Sound", meta = (AllowPrivateAccess = "true"))
	float SliderSpringbackSoundStartTime;

	//
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Slider Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundAttenuation> SoundAttenuation;

	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HapticFeedbackEffect, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHapticFeedbackEffect_Base> SliderbackFeedbackEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Buffer, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UGameplayEffect> BulletConsumeClass;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	TObjectPtr<UAnimMontage> EmptyOpenFireMontage;
public:
	AVRGunBase();

protected:
	virtual void Grab();
	virtual void Release();

protected:
	void BindAction();
	void RemoveAction();

	virtual void TriggerLeft(const FInputActionValue& InInputValue);
	virtual void TriggerRight(const FInputActionValue& InInputValue);

	virtual void OpenFire(const FInputActionValue& InInputValue);

public:
	virtual void HandlingBullets(AVRClipBase* InClipBase, float InCurrentBulletNumber, float InNumberBulletsLeft, bool bInstallClip);
	virtual void SetBulletNumber(AVRClipBase* InClipBase, bool bInstallClip, bool bHandlingBullets = true);

public:
	void CheckNeedLoading();

public:
	UFUNCTION(BlueprintCallable, Category = "Gun")
	void PlayEmptyOpenFireMontage();

public:
	UFUNCTION(BlueprintPure, Category = "Gun|Bullet")
	bool IsEnoughBullets()const;

	UFUNCTION(BlueprintPure, Category = "Gun|Bullet")
	bool IsFullBullets()const;

	UFUNCTION(BlueprintPure, Category = "Gun|Bullet")
	bool IsUpperSpringClip() const { return bUpperSpringClip; }
public:
	EVRHandType GetHandType()const;
	UInputMappingContext* GetInputMappingContext()const;

	UFUNCTION(BlueprintPure, Category = "Gun|Position")
	FVector GetIncrementPosition()const;

	UFUNCTION(BlueprintPure, Category = "Gun|ClipActor")
	AVRClipBase* GetClipActor() const;

	UFUNCTION(BlueprintPure, Category = "Gun|Position")
	FVector GetRelativeAttachParentActorPosition() const;

public:
	virtual UVRAttributeSetBase* GetAttribute() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

protected:
	virtual void OnSlingClip();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	virtual void OnSliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UFUNCTION()
	virtual void OnClipBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnClipEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UFUNCTION()
		virtual void OnStartPullup();

	UFUNCTION()
		virtual void OnEndPullup();

	UFUNCTION()
		virtual void OnStartSpringback();

	UFUNCTION()
		virtual void OnEndSpringback();

	UFUNCTION()
		virtual void OnSliding(float InRatio, bool bRebound);

private:
	//��һ�ε�pos
	UPROPERTY()
	FVector LastRelativeAttachParentActorPosition;

	//��¼�� �����Ƴ�
	FInputBindingHandle* LeftHandle;
	FInputBindingHandle* RightHandle;

	//�����Handle
	FGameplayAbilitySpecHandle OpenFireHandle;

	//����
	UPROPERTY()
	bool bLoading;

	//��һ�� Ĭ��Ϊtrue �����ǹ�ӵ������� ���ֵĬ��Ϊfalse ֻ�б����ӵ�����Ϊfalse �ϵ��к����ֵΪtrue
	//���ֵֻ�����ڶ�����ͼ
	UPROPERTY()
	bool bUpperSpringClip;
};
