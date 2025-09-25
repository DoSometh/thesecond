// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/BoxComponent.h"
#include "SimpleSliderComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FStartPullupDynamicMulticast, USimpleSliderComponent, StartPullupDelegate);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FEndPullupDynamicMulticast, USimpleSliderComponent, EndPullupDelegate);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FStartSpringbackDynamicMulticast, USimpleSliderComponent, StartSpringbackDelegate);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FEndSpringbackDynamicMulticast, USimpleSliderComponent, EndSpringbackDelegate);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FSlidingDynamicMulticast, USimpleSliderComponent, SlidingDelegate, float, InRatio, bool, bRebound);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleSliderComponent : public UBoxComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Slider, meta = (AllowPrivateAccess = "true"))
	float SliderRelativeDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Slider, meta = (AllowPrivateAccess = "true"))
	bool bSpringback;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Slider, meta = (AllowPrivateAccess = "true"))
	float SpringbackSpeed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Drag, meta = (AllowPrivateAccess = "true"))
	bool bEnablePosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragX, meta = (EditCondition = "bEnablePositionX", AllowPrivateAccess = "true"))
	bool bEnablePositionX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragX, meta = (EditCondition = "bEnablePositionX", AllowPrivateAccess = "true"))
	bool bEnablePositionNegativeX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragX, meta = (EditCondition = "bEnablePositionX", AllowPrivateAccess = "true"))
	bool bEnablePositionPositiveX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragY, meta = (EditCondition = "bEnablePosition", AllowPrivateAccess = "true"))
	bool bEnablePositionY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragY, meta = (EditCondition = "bEnablePositionY", AllowPrivateAccess = "true"))
	bool bEnablePositionNegativeY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragY, meta = (EditCondition = "bEnablePositionY", AllowPrivateAccess = "true"))
	bool bEnablePositionPositiveY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragZ, meta = (EditCondition = "bEnablePosition", AllowPrivateAccess = "true"))
	bool bEnablePositionZ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragZ, meta = (EditCondition = "bEnablePositionZ", AllowPrivateAccess = "true"))
	bool bEnablePositionNegativeZ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragZ, meta = (EditCondition = "bEnablePositionZ", AllowPrivateAccess = "true"))
	bool bEnablePositionPositiveZ;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Drag, meta = (AllowPrivateAccess = "true"))
	bool bEnableRotator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragYaw, meta = (EditCondition = "bEnableRotator", AllowPrivateAccess = "true"))
	bool bEnableRotatorYaw;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragRoll, meta = (EditCondition = "bEnableRotator", AllowPrivateAccess = "true"))
	bool bEnableRotatorRoll;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DragPitch, meta = (EditCondition = "bEnableRotator", AllowPrivateAccess = "true"))
	bool bEnableRotatorPitch;

public:	
	UPROPERTY(BlueprintAssignable, Category = Slider, meta = (DisplayName = "Pullup"))
	FStartPullupDynamicMulticast StartPullupDelegate;
	//拉到底 激活当前代理
	UPROPERTY(BlueprintAssignable, Category = Slider, meta = (DisplayName = "Pullup"))
	FEndPullupDynamicMulticast EndPullupDelegate;

	UPROPERTY(BlueprintAssignable, Category = Slider, meta = (DisplayName = "Springback"))
	FStartSpringbackDynamicMulticast StartSpringbackDelegate;

	//松开 复原后激活当前代理
	UPROPERTY(BlueprintAssignable, Category = Slider, meta = (DisplayName = "Springback"))
	FEndSpringbackDynamicMulticast EndSpringbackDelegate;

	//滑动中会激活该代理
	UPROPERTY(BlueprintAssignable, Category = Slider, meta = (DisplayName = "Sliding"))
	FSlidingDynamicMulticast SlidingDelegate;

public:
	USimpleSliderComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintPure, Category = "Components|Position")
	FVector IsAllowPosition(const FVector& InVector);

	UFUNCTION(BlueprintPure, Category = "Components|Position")
	FVector IsAllowPNPosition(const FVector& InVector);

	UFUNCTION(BlueprintPure, Category = "Components|Rotator")
	FRotator IsAllowRotator(const FRotator& InRotator);

	UFUNCTION(BlueprintPure, Category = "Components|Position")
	FVector GetIncrementPosition()const { return IncrementPosition; }

public:
	void StartSlider(float DeltaTime);
	void EndAutomaticSlider(float DeltaTime);
	void EndSlider(float DeltaTime);

protected:
	float IsAllowInputXPNAxis(const FVector& InVector);
	float IsAllowInputYPNAxis(const FVector& InVector);
	float IsAllowInputZPNAxis(const FVector& InVector);

	float IsAllowInputXAxis(const FVector& InVector);
	float IsAllowInputYAxis(const FVector& InVector);
	float IsAllowInputZAxis(const FVector& InVector);

	float IsAllowInputYawAxis(const FRotator& InRotator);
	float IsAllowInputRollAxis(const FRotator& InRotator);
	float IsAllowInputPitchAxis(const FRotator& InRotator);

	float IsAllowInputPNAxis(bool bNegative, bool bPositive, float InValue);
public:
	UFUNCTION(BlueprintCallable, Category = "Components|Drag")
	void SetGrab(bool InNewGrab) { bGrab = InNewGrab; }

	UFUNCTION(BlueprintCallable, Category = "Components|Drag")
	void SetInitializeDragPosition(const FVector& InVector) { InitializeDragPosition = InVector; }
	
	UFUNCTION(BlueprintCallable, Category = "Components|Drag")
	void SetDragPosition(const FVector& InVector) { DragPosition = InVector; }

	UFUNCTION(BlueprintCallable, Category = "Components|Drag")
	void SetInitializeDragRotator(const FRotator& InRotator) { InitializeDragRotator = InRotator; }
	
	UFUNCTION(BlueprintCallable, Category = "Components|Drag")
	void SetDragRotator(const FRotator& InRotator) { DragRotator = InRotator; }
public:

	UFUNCTION(BlueprintPure, Category = "Components|Drag")
	FORCEINLINE bool IsGrab()const { return bGrab; }

protected:
	//描述 从 A->B的过程
	UPROPERTY()
	FVector IncrementPosition;

	//记录拖拽的起始位置
	UPROPERTY()
	FVector InitializeDragPosition;

	//当前拖拽位置
	UPROPERTY()
	FVector DragPosition;

	//旋转拖拽
	UPROPERTY()
	FRotator InitializeDragRotator;

	//当前的旋转拖拽
	UPROPERTY()
	FRotator DragRotator;

	//记录组件的相对位置
	UPROPERTY()
	FVector InitializeRelativePosition;

	//记录组件的旋转相对位置
	UPROPERTY()
	FRotator InitializeRelativeRotator;

	//是否握住
	UPROPERTY()
	bool bGrab;

	//开始准备回弹
	UPROPERTY()
	bool bEnableStartSpringbackEvent;

	UPROPERTY()
	bool bEnableStartPullEvent;
};