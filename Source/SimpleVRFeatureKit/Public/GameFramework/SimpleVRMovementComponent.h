//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleVRMovementComponent.generated.h"

UCLASS()
class SIMPLEVRFEATUREKIT_API USimpleVRMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	USimpleVRMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations);

public:
	void AddCustomInputVector(const FVector& InNewInputVector);
	void ClearCustomInputVector();

private:
	FVector CustomVRInputVector;
};