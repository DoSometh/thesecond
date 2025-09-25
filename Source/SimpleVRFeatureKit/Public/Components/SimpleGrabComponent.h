// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SimpleVRFeatureKitType.h"
#include "SimpleGrabComponent.generated.h"

class UMotionControllerComponent;
class UHapticFeedbackEffect_Base;
enum class EControllerHand : uint8;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FGrabDynamicMulticast, USimpleGrabComponent, GrabDelegate);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FReleaseDynamicMulticast, USimpleGrabComponent, ReleaseDelegate);

UCLASS(ClassGroup=(Custom),meta=(BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleGrabComponent : public USceneComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HapticFeedbackEffect, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHapticFeedbackEffect_Base> PickupFeedbackEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HapticFeedbackEffect, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHapticFeedbackEffect_Base> ReleaseFeedbackEffect;

	//拾取方式
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	EGrabType GrabType;

public:
	UPROPERTY(BlueprintAssignable, Category = Grab, meta = (DisplayName = "Grab Changed"))
	FGrabDynamicMulticast GrabDelegate;

	UPROPERTY(BlueprintAssignable, Category = Grab, meta = (DisplayName = "Release Changed"))
	FReleaseDynamicMulticast ReleaseDelegate;

public:	
	// Sets default values for this component's properties
	USimpleGrabComponent();

public:
	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	bool TryGrab(UMotionControllerComponent* InMotionController,AActor* InAttachActor = NULL);

	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	bool TryRelease();

public:
	void SetPrimitiveCompPhysics(bool bSimulate);
	bool AttachParentToMotionController(UMotionControllerComponent* InMotionController);

public:
	//内部调用 确保已经拾取到物体了 
	UFUNCTION(BlueprintCallable, Category = "Components|Haptic")
	bool PlayHapticEffect(UHapticFeedbackEffect_Base* InEffect, float InScale = 1.f, bool bLoop = false);

	UFUNCTION(BlueprintCallable, Category = "Components|Grab")
	void SetGrabType(EGrabType InGrabType);

	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	FRotator GetGrabPointRelativeRotation() const;

	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	FVector GetGrabPointRelativeLocation() const;

public:
	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	FORCEINLINE EGrabType GetGrabType() const { return GrabType; }

	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	FORCEINLINE bool IsHeld() const { return bHeld; }

	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	FORCEINLINE AActor* GetAttachObject() const { return AttachActor; }

	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	EGrabTrackingType GetGrabTrackingType();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	virtual void InitGrabComponent();

protected:

	void Held(UMotionControllerComponent* InMotionController);
public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	//握住的状态
	UPROPERTY()
	bool bHeld;

	//是不是模拟物理
	UPROPERTY()
	bool bSimulateOnDrop;

	UPROPERTY()
	UMotionControllerComponent* RefMotionController;

	//Attach对象的引用
	UPROPERTY()
	AActor* AttachActor;
};
