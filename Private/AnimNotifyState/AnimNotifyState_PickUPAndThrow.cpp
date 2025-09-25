//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotifyState/AnimNotifyState_PickUPAndThrow.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleComboType.h"
#include "Components/SkeletalMeshComponent.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "SimpleCombatBPLibrary.h"

UAnimNotifyState_PickUPAndThrow::UAnimNotifyState_PickUPAndThrow()
	:Super()
{
	BindSocket = TEXT("hand_r");
	Speed = 1600.f;
	LiftTime = 10.f;
	bHoming = false;
	HitID = INDEX_NONE;
	bSelfRotation = false;
}

void UAnimNotifyState_PickUPAndThrow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		if (ActorClass)
		{
			FVector BindSocketLocation = MeshComp->GetSocketLocation(BindSocket);
			FRotator BindSocketRotation = MeshComp->GetSocketRotation(BindSocket);
			
			if (AActor* InActor = USimpleCombatBPLibrary::SpawnSimpleCollisionByTags(
				InCharacter,
				ActorClass,
				BindSocketLocation,
				BindSocketRotation, 
				BuffTags, 
				GASTag,
				HitID, 
				LiftTime))
			{
				FVector InScale3D = MeshComp->GetComponentScale();
				InActor->SetActorScale3D(InScale3D);

				FAttachmentTransformRules TransformRules(
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::SnapToTarget, 
					EAttachmentRule::KeepWorld,false);

				InActor->AttachToComponent(MeshComp, TransformRules, BindSocket);
			}
		}
	}
}

void UAnimNotifyState_PickUPAndThrow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);


}

void UAnimNotifyState_PickUPAndThrow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		if (ISimpleComboInterface* InComboInterface = Cast<ISimpleComboInterface>(InCharacter))
		{
			if (AActor *InTarget = InComboInterface->GetTarget())
			{
				const TArray<TObjectPtr<USceneComponent>> Childrens = MeshComp->GetAttachChildren();

				AHitCollision* HitBox = nullptr;
				for (auto& Tmp : Childrens)
				{
					if (AHitCollision* InHitBox = Cast<AHitCollision>(Tmp->GetOwner()))
					{
						HitBox = InHitBox;
						break;
					}
				}

				if (HitBox)
				{
					HitBox->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));

					FVector OwnerToTarget = InTarget->GetActorLocation() - InCharacter->GetActorLocation();
					OwnerToTarget.Normalize();
					
					if (bHoming)
					{
						HitBox->ActivateProjectileMovementHoming(InTarget, Speed, bSelfRotation);
					}
					else
					{
						HitBox->ActivateProjectileMovement(Speed, Speed * OwnerToTarget, true, bSelfRotation);
					}
				}
			}
		}
	}
}