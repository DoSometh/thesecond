#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GameFramework/SpringArmComponent.h"
#include "SimplePsychokinesisComponent.generated.h"

class UHapticFeedbackEffect_Base;
class UMotionControllerComponent;

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FPsychokinesisDynamicMulticast, USimplePsychokinesisComponent, OnPsychokinesisDynamicDelegate, USimplePsychokinesisComponent*, InPsychokinesisComponent, float, InLenght);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimplePsychokinesisComponent : public USpringArmComponent
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Parts, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SubitemComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HapticFeedbackEffect, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHapticFeedbackEffect_Base> TouchFeedbackEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = HapticFeedbackEffect, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UHapticFeedbackEffect_Base> ControlFeedbackEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float TraceInterval;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float SpeedAttraction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float MinimumAttractionDistance;

	UPROPERTY()
	float CurrentTraceCount;

public:
	USimplePsychokinesisComponent();

public:
	UPROPERTY(BlueprintAssignable, Category = Psychokinesis)
	FPsychokinesisDynamicMulticast OnPsychokinesisDynamicDelegate;

public:
	void SetMotionControllerComponent(UMotionControllerComponent* InMotionControllerComponent);

	void StartPsychokinesis();
	void UpdateAttractiveForce(float DeltaTime);
	void EndPsychokinesis();

	void SetNewGrabComponent(UPrimitiveComponent* InNewComponent);

public:
	bool IsPsychokinesis() const { return bPsychokinesis; }
	bool IsExitControlledComponent() const { return ControlledComponent.IsValid(); }

protected:
	void ResetTargetArmLength();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TWeakObjectPtr<UPrimitiveComponent> ControlledComponent;

	UPROPERTY()
	TWeakObjectPtr<UMotionControllerComponent> RefMotionController;

	UPROPERTY()
	bool bPsychokinesis;
};