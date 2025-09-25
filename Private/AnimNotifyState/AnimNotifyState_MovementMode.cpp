
//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "AnimNotifyState/AnimNotifyState_MovementMode.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

UAnimNotifyState_MovementMode::UAnimNotifyState_MovementMode()
{
	bLeaveItAsItIs = true;
}

void UAnimNotifyState_MovementMode::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
		{
			if (UCharacterMovementComponent* InCharacterMovementComponent = Cast<UCharacterMovementComponent>(InCharacter->GetCharacterMovement()))
			{
				CharacterMovementMode = InCharacterMovementComponent->MovementMode;

				if (InCharacterMovementComponent->MovementMode != MovementMode)
				{
					InCharacterMovementComponent->SetMovementMode(MovementMode);
				}
			}
		}
	}
}

void UAnimNotifyState_MovementMode::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void UAnimNotifyState_MovementMode::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (MeshComp->GetOuter() && MeshComp->GetOuter()->GetWorld())
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
		{
			if (UCharacterMovementComponent* InCharacterMovementComponent = Cast<UCharacterMovementComponent>(InCharacter->GetCharacterMovement()))
			{
				if (bLeaveItAsItIs)
				{
					if (InCharacterMovementComponent->MovementMode != CharacterMovementMode)
					{
						InCharacterMovementComponent->SetMovementMode(CharacterMovementMode);
					}
				}
				else
				{
					InCharacterMovementComponent->SetMovementMode(EndMovementMode);
				}	
			}
		}
	}
}