//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "AnimNotifyState/AnimNotifyState_ForceFaceTarget.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleComboType.h"
#include "Components/SkeletalMeshComponent.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "Components/SkeletalMeshComponent.h"

UAnimNotifyState_ForceFaceTarget::UAnimNotifyState_ForceFaceTarget()
	:Super()
{
	bYaw = true;
	bPitch = false;
	bRoll = false;
}

void UAnimNotifyState_ForceFaceTarget::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

}

void UAnimNotifyState_ForceFaceTarget::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (ISimpleComboInterface* InSimpleCombatInterface = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
	{
		if (AActor* InTarget = InSimpleCombatInterface->GetTarget())
		{
			if (AActor* InThis = Cast<AActor>(MeshComp->GetOuter()))
			{
				FMatrix Matrix = FRotationMatrix::MakeFromX(InTarget->GetActorLocation() - InThis->GetActorLocation());
				FRotator FaceRot = Matrix.Rotator();

				auto ResetRotatorValue = [](bool bReset, void* InData)->float
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

				InThis->SetActorRotation(FaceRot);
			}
		}
	}
}

void UAnimNotifyState_ForceFaceTarget::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
