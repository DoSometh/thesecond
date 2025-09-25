//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "AnimNotifyState/AnimNotifyState_MoveToTarget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleComboType.h"
#include "Components/SkeletalMeshComponent.h"
#include "CombatInterface/SimpleCombatInterface.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

//只能单个对象使用
struct FMoveToTargetTmpData :public FInternallyInterpolatedStructureTmpData
{
	FTransform CurrentTransform;
};

TMap<int32, FMoveToTargetTmpData> MoveToTargetPools;

UAnimNotifyState_MoveToTarget::UAnimNotifyState_MoveToTarget()
	:Super()
{
	OverlappingDistance = 100.f;
}

void UAnimNotifyState_MoveToTarget::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (MoveToTargetPools.Contains(InCharacter->GetUniqueID()))
		{
			MoveToTargetPools.Remove(InCharacter->GetUniqueID());
		}

		FMoveToTargetTmpData& InArmTmpData = MoveToTargetPools.Add(InCharacter->GetUniqueID());
		InArmTmpData.NotifyStateTotalDuration = TotalDuration;
		InArmTmpData.CurrentTransform = InCharacter->GetTransform();
	}
}

void UAnimNotifyState_MoveToTarget::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (ISimpleComboInterface* InComboInterface = Cast<ISimpleComboInterface>(InCharacter))
		{
			if (AActor* InTargetActor = InComboInterface->GetTarget())
			{
				FVector OnwerToTarget = InTargetActor->GetActorLocation() - InCharacter->GetActorLocation();
				OnwerToTarget.Normalize();

				FVector TargetToOnwer = -OnwerToTarget;

				FVector TargetPoint = InTargetActor->GetActorLocation() + TargetToOnwer * OverlappingDistance;

				if (MoveToTargetPools.Contains(InCharacter->GetUniqueID()))
				{
					float InValue = MoveToTargetPools[InCharacter->GetUniqueID()].GetValue(FrameDeltaTime);

					FVector NewLocation = FMath::Lerp(MoveToTargetPools[InCharacter->GetUniqueID()].CurrentTransform.GetLocation(), TargetPoint, InValue);
					FQuat NewQuat = FQuat::Slerp(MoveToTargetPools[InCharacter->GetUniqueID()].CurrentTransform.GetRotation(), OnwerToTarget.Rotation().Quaternion(), InValue);

					//矫正 防止pitch和roll有其他值
					FRotator MyRotator = NewQuat.Rotator();
					MyRotator.Pitch = 0.f;
					MyRotator.Roll = 0.f;

					InCharacter->SetActorLocation(NewLocation);
					InCharacter->SetActorRotation(MyRotator);
				}
			}
		}
	}
}

void UAnimNotifyState_MoveToTarget::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		MoveToTargetPools.Remove(InCharacter->GetUniqueID());
	}
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif
