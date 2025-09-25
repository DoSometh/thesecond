//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotify/AnimNotify_Detach.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/ConstraintInstance.h"

UAnimNotify_Detach::UAnimNotify_Detach()
{
	bResetRotation = false;
	bResetLocation = false;

	bReverseAddition = false;
}

FString UAnimNotify_Detach::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Detach::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (!bReverseAddition)
		{
			// 启用布娃娃物理
			TArray<TObjectPtr<USceneComponent>> SceneChildern = InCharacter->GetMesh()->GetAttachChildren();
			SceneChildern.Add(InCharacter->GetMesh());

			if (UChildActorComponent* InChildActorComponent = SimpleCombatCore::RecursiveSearchComponentsByTag(
				InCharacter->GetRootComponent(),
				ActorClass,
				SubTag))
			{
				if (AActor* InActor = InChildActorComponent->GetChildActor())
				{
					if (bResetRotation)
					{
						InActor->SetActorRelativeRotation(DetachRotation);
					}

					if (bResetLocation)
					{
						InActor->SetActorRelativeLocation(DetachLocation);
					}

					FDetachmentTransformRules TransformRules(EDetachmentRule::KeepWorld, false);
					InActor->DetachFromActor(TransformRules);
				}
			}
		}
		else
		{
			if (bResetRotation)
			{
				InCharacter->SetActorRelativeRotation(DetachRotation);
			}

			if (bResetLocation)
			{
				InCharacter->SetActorRelativeLocation(DetachLocation);
			}

			FDetachmentTransformRules TransformRules(EDetachmentRule::KeepWorld, false);
			InCharacter->DetachFromActor(TransformRules);
		}
	}
}