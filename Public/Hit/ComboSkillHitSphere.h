//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Hit/Core/ComboSkillHitCollision.h"
#include "ComboSkillHitSphere.generated.h"

class USphereComponent;

UCLASS(BlueprintType, Blueprintable)
class SIMPLECOMBAT_API AHitSphereCollision : public AHitCollision
{
	GENERATED_BODY()

	//碰撞盒子
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> HitDamage;

public:
	AHitSphereCollision(const FObjectInitializer& ObjectInitializer);

	virtual UPrimitiveComponent* GetHitDamage();

	void SetRadius(const float& InRadius);

public:
	virtual FVector GetExtent() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual void StartHandleDamage_Inner(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};