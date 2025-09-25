#pragma once

#include "CoreMinimal.h"
#include "SimpleComboType.h"

namespace SimpleCombatCore
{
	USceneComponent* RecursiveSearchComponentsByTag(USceneComponent* InComponent, FName InTag);
	UChildActorComponent *RecursiveSearchComponentsByTag(USceneComponent* InComponent,UClass *InClass, FName InTag);

	//获取物理表面类型
	ESimplePhysicalSurfaceImpactType SIMPLECOMBAT_API GetPhysicalSurfaceType(const FHitResult& InSweepResult);
}