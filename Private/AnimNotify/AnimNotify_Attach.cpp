//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotify/AnimNotify_Attach.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/ConstraintInstance.h"
#include "Kismet/GameplayStatics.h"

UAnimNotify_Attach::UAnimNotify_Attach()
{
	LocationRule = EAttachmentRule::KeepWorld;
	RotationRule = EAttachmentRule::KeepWorld;
	ScaleRule = EAttachmentRule::KeepWorld;

	bInWeldSimulatedBodies = false;

	bReverseAddition = false;
}

FString UAnimNotify_Attach::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		TArray<AActor*> AllActors;

		//找到要附加的实例
		UGameplayStatics::GetAllActorsOfClass(InCharacter->GetWorld(), ActorClass, AllActors);

		AActor* InMyActor = nullptr;
		if (AllActors.Num() > 0)
		{
			InMyActor = AllActors[0];
		}

		if (InMyActor)
		{
			//找到准备附加组件
			USceneComponent* InMeshComp = nullptr;
			if (!bReverseAddition)
			{
				if (MeshComp->ComponentTags.Contains(SubTag))
				{
					InMeshComp = MeshComp;
				}
				else
				{
					InMeshComp = SimpleCombatCore::RecursiveSearchComponentsByTag(InCharacter->GetRootComponent(), SubTag);
				}
			}
			else
			{
				InMeshComp = SimpleCombatCore::RecursiveSearchComponentsByTag(InMyActor->GetRootComponent(), SubTag);
			}
			
			if (InMeshComp)
			{
				FAttachmentTransformRules TransformRules(LocationRule, RotationRule, ScaleRule, bInWeldSimulatedBodies);
				if (!bReverseAddition)
				{	
					InMyActor->AttachToComponent(InMeshComp, TransformRules, AttachSocketName);
				}
				else
				{
					InCharacter->AttachToComponent(InMeshComp, TransformRules, AttachSocketName);
				}			
			}
		}
	}
}
