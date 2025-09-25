// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hit/ComboSkillHitBox.h"
#include "VRBullet.generated.h"

/**
 *
 */
UCLASS()
class SHOOTERVR_API AVRBullet : public AHitBoxCollision
{
	GENERATED_BODY()

public:
	AVRBullet(const FObjectInitializer& ObjectInitializer);

	virtual void HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
