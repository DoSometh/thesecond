//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotifyState/AnimNotifyState_AttachPoint.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleComboType.h"
#include "Components/SkeletalMeshComponent.h"
#include "CombatInterface/SimpleCombatInterface.h"

UAnimNotifyState_AttachPoint::UAnimNotifyState_AttachPoint()
	:Super()
{
	Distance = 200.f;
	Angle = 90.f;
}

void UAnimNotifyState_AttachPoint::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ISimpleComboInterface* InCharacter = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
	{
		if (AActor* InTarget = InCharacter->GetTarget())
		{
			FSimpleAttachPointInfo PointInfo;
			PointInfo.TargetLocation = InTarget->GetActorLocation();
			PointInfo.Value = 0.f;

			InCharacter->Update_AttachPoint(PointInfo, AttachPointTag, false);
		}
	}
}

void UAnimNotifyState_AttachPoint::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (AActor* InOnwerActor = Cast<AActor>(MeshComp->GetOuter()))
	{
		if (ISimpleComboInterface* InCharacter = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
		{
			if (AActor* InTarget = InCharacter->GetTarget())
			{
				float InNewDistance = FVector::Distance(InOnwerActor->GetActorLocation(), InTarget->GetActorLocation());

				if (InNewDistance <= Distance)
				{
					FVector OnwerToTargetDir = InTarget->GetActorLocation() - InOnwerActor->GetActorLocation();
					OnwerToTargetDir.Normalize();

					FSimpleAttachPointInfo PointInfo;
					PointInfo.TargetLocation = InTarget->GetActorLocation();
					PointInfo.Value += FrameDeltaTime;

					PointInfo.Value = FMath::Clamp(PointInfo.Value, 0.f, 1.f);

					float InNewDegrees = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(OnwerToTargetDir, InOnwerActor->GetActorForwardVector())));
					if (InNewDegrees <= Angle)
					{
						InCharacter->Update_AttachPoint(PointInfo, AttachPointTag, false);
					}
					else
					{
						InCharacter->Update_AttachPoint(PointInfo, AttachPointTag, true);
					}
				}
			}
		}
	}
}

void UAnimNotifyState_AttachPoint::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ISimpleComboInterface* InCharacter = Cast<ISimpleComboInterface>(MeshComp->GetOuter()))
	{
		if (AActor* InTarget = InCharacter->GetTarget())
		{
			float InNewDistance = FVector::Distance(Cast<AActor>(MeshComp->GetOuter())->GetActorLocation(), InTarget->GetActorLocation());

			FSimpleAttachPointInfo PointInfo;
			PointInfo.TargetLocation = InTarget->GetActorLocation();
			PointInfo.Value = 1.f;

			InCharacter->Update_AttachPoint(PointInfo, AttachPointTag, true);
		}
	}
}