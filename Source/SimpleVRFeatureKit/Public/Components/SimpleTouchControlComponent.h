// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/ActorComponent.h"
#include "SimpleVRFeatureKitType.h"
#include "SimpleTouchControlComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleTouchControlComponent : public UActorComponent
{
	GENERATED_BODY()
	
	/*
	*Default
	 Hand Right//0
	 Hand Left/1
	 Leg Right/2
	 Leg Left//3
	 Head//4
	 Pelvis//5
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Slider, meta = (AllowPrivateAccess = "true"))
	TMap<uint8,FSimpleTouchControlIncremental> ChainIncrementalMap;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Slider, meta = (AllowPrivateAccess = "true"))
	EIncrementSpringbackType IncrementSpringbackType;
public:

	USimpleTouchControlComponent();

public:
	virtual FTouchControlHandle StartTouch(FName BoneName,USceneComponent *InController);
	virtual void EndTouch(FTouchControlHandle InHandle);

public:
	FTouchControlHandle SpawnUniqueHandle() const;

	FSimpleTouchControlIncremental *FindTouchControlIncremental(FName BoneName);

public:
	virtual void SpawnDefaultHumanChainIncremental();

public:
	TMap<uint8, FSimpleTouchControlIncremental>* GetChainIncrementalMap();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TMap<int32,FSimpleTouchControlInfo> TouchControlInfoPool;

	UPROPERTY()
	TArray<FName> LHand;

	UPROPERTY()
	TArray<FName> RHand;
};