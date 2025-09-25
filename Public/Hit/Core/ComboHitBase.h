//Copyright (C) RenZhai.2022.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "SimpleComboType.h"
#include "ComboHitBase.generated.h"

class UProjectileMovementComponent;

UCLASS(BlueprintType, Blueprintable)
class SIMPLECOMBAT_API AComboHitBase : public AActor
{
	GENERATED_BODY()

protected:
	//碰撞体的主要根组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> HitCollisionRootComponent;

	//碰撞体的主要运动组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
	
public:
	AComboHitBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

public:
	//由外部调用
	UFUNCTION(BlueprintNativeEvent, Category = "Event")
	void OnDeleted(float InTime);
	virtual void OnDeleted_Implementation(float InTime);

	UProjectileMovementComponent* GetProjectileMovementComponent() const;
};