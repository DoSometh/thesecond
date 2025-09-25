//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SimpleAttackInterface.generated.h"

class APawn;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class USimpleAttackInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLECOMBAT_API ISimpleAttackInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual APawn* GetCaster()const { return NULL; }
	virtual bool IsAllowAttack() const { return true; }
	virtual bool IsEnableOnlyLocalAttack() const { return false; }

	virtual void PreLaunchAttack() {}
	virtual void LaunchAttack(AActor* InCollidingBody) {}
	virtual void PostLaunchAttack(AActor* InCollidingBody) {}
	virtual void SpawnCollisionFail() {}//失败

	//获取目标点
	virtual FVector GetTargetPointLocation() const { return FVector(); }
};
