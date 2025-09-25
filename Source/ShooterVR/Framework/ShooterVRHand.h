// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleModularActor.h"
#include "ShooterVRHand.generated.h"

enum class EVRHandType :uint8;
class USkeletalMeshComponent;
class USceneComponent;
class UMotionControllerComponent;
class USimpleGrabComponent;
class USplineComponent;
class UHapticFeedbackEffect_Base;
class USphereComponent;
class USimpleSliderComponent;

/**
 * 
 */
UCLASS()
class SHOOTERVR_API AShooterVRHand : public ASimpleModularActor
{
	friend class AShooterVRCharacter;

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	EVRHandType HandType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> HandMesh;
	
	//曲线
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VRController, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USplineComponent> Spline;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VRController, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> VRSystem;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float GrabRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Drag, meta = (AllowPrivateAccess = "true"))
	float DragDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Drag, meta = (AllowPrivateAccess = "true"))
	float CurvilinearDegree;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Drag, meta = (AllowPrivateAccess = "true"))
	float DragAxisValue;

	//是否开启拖拽绘制
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Drag, meta = (AllowPrivateAccess = "true"))
	bool bDragDebugSphere;

	//拖拽的曲线分段
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Drag, meta = (AllowPrivateAccess = "true"))
	int32 DragSubsection;

	//选择的震动
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HapticFeedbackEffect, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHapticFeedbackEffect_Base> ChoiceFeedbackEffect;

	//拖拽震动
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HapticFeedbackEffect, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHapticFeedbackEffect_Base> DragFeedbackEffect;
public:
	AShooterVRHand();

	void InitShooterVRHand(UMotionControllerComponent* InMotionController);

	void Grab(UMotionControllerComponent* InMotionController);
	void TryRelease();
	bool Release();

	void Drag(UMotionControllerComponent* InMotionController);
	void DragEnd();

	void Pickup(UMotionControllerComponent* InMotionController);
	FVector GetMotionControllerSliderLocation(UMotionControllerComponent* InMotionController = NULL);
public:
	void MoveItem(USimpleGrabComponent* InNewHeldComponent);
	void SwapAndOtherHand(USimpleGrabComponent* InBNewHeldComponent);

	void ClearHeldComponent();
	void SetHeldComponent(USimpleGrabComponent* InNewHeldComponent);
public:
	void DrawArrayPointLine(const FVector &InStart,const FVector &InEnd,TArray<FVector> &OutVector);
public:
	USimpleGrabComponent* GetGrabComponentNearMotionController(const FVector& InMotionControllerLocation);
	USimpleSliderComponent* GetSliderComponentOverlapMotionController(const FVector& InMotionControllerLocation);

	//Find the object type that the component passes over
	USimpleGrabComponent* FindLatelyGrabComponentByClass(const FVector& InMotionControllerLocation, TArray<UActorComponent*> GrabComponents, UClass* InExcludeParentObjectClass = NULL);
protected:
	bool TraceItemComponents(const FVector& InMotionControllerLocation, TFunction<bool(const FHitResult&)> InFun);

protected:
	bool IsDragAction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE EVRHandType GetHandType()const { return HandType; }
	FORCEINLINE UMotionControllerComponent* GetMotionController() const { return RefMotionController; }
	FORCEINLINE void SetEnableSliderTrace(bool bNewEnableSlider) { bEnableSliderTrace = bNewEnableSlider; }

protected:
	UPROPERTY()
	USimpleGrabComponent* HeldComponent;

	UPROPERTY()
	USimpleSliderComponent* SliderComponent;

protected:
	//上一个被敲击的对象
	UPROPERTY()
	AActor* LastAllowHitObject;

	//上一次的旋转
	UPROPERTY()
	FRotator LastRotator;

	//是否准备拖拽
	UPROPERTY()
	bool bPrepareDrag;

	//拖拽
	UPROPERTY()
	bool bDrag;

	//是否开启滑条检测
	UPROPERTY()
	bool bEnableSliderTrace;

	//是否握住
	UPROPERTY()
	bool bGrab;

	//决定要拖拽的对象
	UPROPERTY()
	AActor* DragTarget;

	UPROPERTY()
	FVector DragTangent;

	//引用Montion
	UPROPERTY()
	UMotionControllerComponent* RefMotionController;
};
