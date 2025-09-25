  //Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MotionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERVR_API UMotionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMotionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};