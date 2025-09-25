//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotify/AnimNotify_FaceTarget.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimNotify_FaceTarget::UAnimNotify_FaceTarget()
{
	bYaw = true;
	bPitch = false;
	bRoll = false;
}

FString UAnimNotify_FaceTarget::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_FaceTarget::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ISimpleComboInterface *InSimpleCombatInterface = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
	{		
		if (AActor* InTarget = InSimpleCombatInterface->GetTarget())
		{
			if (AActor* InThis = Cast<AActor>(MeshComp->GetOuter()))
			{
				/*FMatrix Matrix = FRotationMatrix::MakeFromX(InTarget->GetActorLocation() - InThis->GetActorLocation());
				FRotator FaceRot = Matrix.Rotator();*/

				FVector Direction = (InTarget->GetActorLocation() - InThis->GetActorLocation()).GetSafeNormal();
				FRotator FaceRot = Direction.Rotation();
				FaceRot.Pitch = 0.0f; // Keep the pitch level
				FaceRot.Roll = 0.0f;  // No rolling

				auto ResetRotatorValue = [](bool bReset,void *InData)->float
				{
					if (!bReset)
					{
						return 0.f;
					}

					return *((float*)InData);
				};

				FaceRot.Yaw = ResetRotatorValue(bYaw, &FaceRot.Yaw);
				FaceRot.Roll = ResetRotatorValue(bRoll, &FaceRot.Roll);
				FaceRot.Pitch = ResetRotatorValue(bPitch, &FaceRot.Pitch);

				if (ACharacter *InCharacter = Cast<ACharacter>(InThis))
				{
					if (UCharacterMovementComponent *InCharacterMovement = InCharacter->GetCharacterMovement())
					{
						if (InCharacterMovement->bOrientRotationToMovement == true)
						{
							InThis->SetActorRotation(FaceRot);
						}
						else
						{
							InCharacter->GetController()->SetControlRotation(FaceRot * -1.f);
						}
					}
				}
			}
		}
	}
}