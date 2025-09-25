//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Hit/Core/ComboSkillHitCollision.h"
#include "ComboSkillHitBox.generated.h"

class UBoxComponent;

UCLASS(BlueprintType, Blueprintable)
class SIMPLECOMBAT_API AHitBoxCollision : public AHitCollision
{
	GENERATED_BODY()

	//碰撞盒子
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttrubute", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> HitDamage;

public:
	AHitBoxCollision(const FObjectInitializer& ObjectInitializer);

	virtual UPrimitiveComponent* GetHitDamage();

	void SetBoxExtent(const FVector& InNewBoxExtent);

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