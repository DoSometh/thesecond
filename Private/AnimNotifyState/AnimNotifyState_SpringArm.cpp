//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotifyState/AnimNotifyState_SpringArm.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

//只能单个对象使用
TMap<int32,FInternallyInterpolatedStructureTmpData> SprintPools;

UAnimNotifyState_SpringArm::UAnimNotifyState_SpringArm()
	:Super()
{
	CurrentArmLength = 470.f;

	TargetArmLength = 500.f;
}

void UAnimNotifyState_SpringArm::NotifyBegin(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation, 
	float TotalDuration, 
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacter *InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (SprintPools.Contains(InCharacter->GetUniqueID()))
		{
			SprintPools.Remove(InCharacter->GetUniqueID());
		}

		FInternallyInterpolatedStructureTmpData& InArmTmpData = SprintPools.Add(InCharacter->GetUniqueID());
		InArmTmpData.NotifyStateTotalDuration = TotalDuration;
	}
}

void UAnimNotifyState_SpringArm::NotifyTick(
	USkeletalMeshComponent* MeshComp, 
	UAnimSequenceBase* Animation,
	float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (ACharacter *InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (USpringArmComponent* InSpringArmComponent = InCharacter->FindComponentByClass<USpringArmComponent>())
		{
			if (SprintPools.Contains(InCharacter->GetUniqueID()))
			{
				float InValue  = SprintPools[InCharacter->GetUniqueID()].GetValue(FrameDeltaTime);

				InSpringArmComponent->TargetArmLength = FMath::Lerp(CurrentArmLength, TargetArmLength, InValue);
			}
		}
	}
}

void UAnimNotifyState_SpringArm::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (USpringArmComponent* InSpringArmComponent = InCharacter->FindComponentByClass<USpringArmComponent>())
		{
			InSpringArmComponent->TargetArmLength = TargetArmLength;

			SprintPools.Remove(InCharacter->GetUniqueID());
		}
	}
}