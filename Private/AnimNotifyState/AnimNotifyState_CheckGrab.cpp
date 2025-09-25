//Copyright (C) RenZhai.2022.All Rights Reserved.\

#include "AnimNotifyState/AnimNotifyState_CheckGrab.h"
#include "SimpleComboType.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

UAnimNotifyState_CheckGrab::UAnimNotifyState_CheckGrab()
{
	TypeQuery = ETraceTypeQuery::TraceTypeQuery1;
	bDrawDebug = false;
	Radius = 10.f;
	Distance = 100.f;
	bEndStopMontage = false;
}

void UAnimNotifyState_CheckGrab::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void UAnimNotifyState_CheckGrab::NotifyTick(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, 
	float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (MeshComp)
	{
		USkeletalMeshComponent* InBindMeshComp = NULL;
		if (!GetGarbCharacter(MeshComp, InBindMeshComp) && InBindMeshComp)
		{
			if (AActor *InMyCharacter = Cast<AActor>(InBindMeshComp->GetOuter()))
			{
				FVector InAttachLocation = InBindMeshComp->GetSocketLocation(GrabSocketName);
				FVector ComponentScale = InBindMeshComp->GetComponentScale();

				TArray<AActor*> ActorsToIgnore;
				ActorsToIgnore.Add(InMyCharacter);

				EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
				if (bDrawDebug)
				{
					DrawDebugType = EDrawDebugTrace::ForDuration;
				}

				FHitResult HitResult;
				if (UKismetSystemLibrary::SphereTraceSingle(
					InMyCharacter->GetWorld(),
					InAttachLocation,
					InAttachLocation + InMyCharacter->GetActorForwardVector() * Distance * ComponentScale.Size(),
					Radius * ComponentScale.Size(),
					TypeQuery,
					false,
					ActorsToIgnore,
					DrawDebugType,
					HitResult,
					true))
				{
					if (ACharacter *InAttachCharacter = Cast<ACharacter>(HitResult.GetActor()))
					{
						if (UCharacterMovementComponent *InCharacterMovementComponent = InAttachCharacter->GetCharacterMovement())
						{
							InCharacterMovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
							InCharacterMovementComponent->GravityScale = 0.f;
						}

						FAttachmentTransformRules TransformRules(
							EAttachmentRule::SnapToTarget,
							EAttachmentRule::SnapToTarget,
							EAttachmentRule::KeepWorld, false);

						InAttachCharacter->AttachToComponent(InBindMeshComp, TransformRules, GrabSocketName);

						if (ISimpleComboInterface *InComboInterface = Cast<ISimpleComboInterface>(InAttachCharacter))
						{
							InComboInterface->CaughtUP(InMyCharacter);
						}
					}
				}
			}
		}
	}
}

void UAnimNotifyState_CheckGrab::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter *InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		USkeletalMeshComponent* InBindMeshComp = NULL;
		if (!GetGarbCharacter(MeshComp, InBindMeshComp) && InBindMeshComp)
		{
			if (bEndStopMontage)
			{
				InCharacter->StopAnimMontage();
			}
		}
	}
}

ACharacter* UAnimNotifyState_CheckGrab::GetGarbCharacter(USkeletalMeshComponent* MeshComp, USkeletalMeshComponent *&InBindMesh) const
{
	if (ACharacter* InOwnerCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (!SubMeshTagName.IsNone())
		{
			InBindMesh = InOwnerCharacter->FindComponentByTag<USkeletalMeshComponent>(SubMeshTagName);
		}

		if (!InBindMesh)
		{
			InBindMesh = MeshComp;
		}

		const TArray<TObjectPtr<USceneComponent>> Childrens = InBindMesh->GetAttachChildren();

		ACharacter* GarbCharacter = nullptr;
		for (auto& Tmp : Childrens)
		{
			if (ACharacter* InCharacter = Cast<ACharacter>(Tmp->GetOwner()))
			{
				if (InCharacter != InOwnerCharacter)
				{
					return InCharacter;
				}
			}
		}
	}

	return nullptr;
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif