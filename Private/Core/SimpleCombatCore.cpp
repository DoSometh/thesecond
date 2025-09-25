// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Core/SimpleCombatCore.h"

UE_DISABLE_OPTIMIZATION

namespace SimpleCombatCore
{
	USceneComponent* RecursiveSearchComponentsByTag(USceneComponent* InComponent, FName InTag)
	{
		if (InComponent)
		{
			TArray<TObjectPtr<USceneComponent>> SceneChildern = InComponent->GetAttachChildren();

			for (auto& Tmp : SceneChildern)
			{
				if (Tmp->ComponentHasTag(InTag))
				{
					return Tmp;
				}
				else
				{
					if (USceneComponent* InFindComponent = RecursiveSearchComponentsByTag(Tmp, InTag))
					{
						return InFindComponent;
					}
				}
			}
		}

		return nullptr;
	}

	UChildActorComponent *RecursiveSearchComponentsByTag(USceneComponent* InComponent, UClass* InClass, FName InTag)
	{
		if (InComponent)
		{
			TArray<TObjectPtr<USceneComponent>> SceneChildern = InComponent->GetAttachChildren();

			for (auto& Tmp : SceneChildern)
			{
				if (Tmp->ComponentHasTag(InTag))
				{
					if (UChildActorComponent *InChildActor = Cast<UChildActorComponent>(Tmp))
					{
						if (!InClass)
						{
							return InChildActor;
						}

						if (InChildActor->GetChildActorClass() == InClass)
						{
							return InChildActor;
						}
					}	
				}
				else
				{
					if (UChildActorComponent* InFindComponent = RecursiveSearchComponentsByTag(Tmp, InClass, InTag))
					{
						return InFindComponent;
					}
				}
			}
		}

		return nullptr;
	}

	ESimplePhysicalSurfaceImpactType GetPhysicalSurfaceType(const FHitResult& InSweepResult)
	{
		if (InSweepResult.PhysMaterial.IsValid())
		{
			//材质名字
			FString InMaterialName = InSweepResult.PhysMaterial->GetName();
			FString EnumString = FString::Printf(TEXT("ESimplePhysicalSurfaceImpactType::PHYSICALSURFACEIMPACT_%s"), *InMaterialName.ToUpper());
		
			int64 NumIndex = UEnum::LookupEnumName(TEXT("/Script/SimpleCombat"),*EnumString);
			return (ESimplePhysicalSurfaceImpactType)NumIndex;
		}
		
		return ESimplePhysicalSurfaceImpactType::PHYSICALSURFACEIMPACT_DEFAULT;
	}
}

UE_ENABLE_OPTIMIZATION