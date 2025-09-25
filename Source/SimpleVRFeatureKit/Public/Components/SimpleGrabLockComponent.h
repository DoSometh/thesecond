// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SimpleVRFeatureKitType.h"
#include "SimpleGrabLockComponent.generated.h"

class UMotionControllerComponent;
class IVRGrabInterface;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleGrabLockComponent : public UBoxComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GrabLock, meta = (AllowPrivateAccess = "true"))
	FRotator RotatorOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float GrabSpeed;

	//附加的一个比较值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float GrabTolerance;

public:
	USimpleGrabLockComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void TickTask(float DeltaTime);

public:
	AActor* GetAttachTopChildren();
	AActor* GetAttachObject();

protected:
	UFUNCTION()
	virtual void OnGrabBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnGrabEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY()
	FSimpleGrabLockInfo SimpleGrabLockInfo;
};