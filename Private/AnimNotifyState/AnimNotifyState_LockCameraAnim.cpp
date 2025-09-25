//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "AnimNotifyState/AnimNotifyState_LockCameraAnim.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleComboType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CombatInterface/SimpleAttackInterface.h"
#include "Camera/CameraActor.h"

UAnimNotifyState_LockCameraAnim::UAnimNotifyState_LockCameraAnim()
	:Super()
{
	bLockCamera = false;
	bReturn = false;
	BlendValue = 1.f;
	Camera = nullptr;
	TargetBlendFunction = ELockCameraAnimViewTargetBlendFunction::VTBlend_Cubic;
}

void UAnimNotifyState_LockCameraAnim::NotifyBegin(USkeletalMeshComponent *MeshComp, UAnimSequenceBase * Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	CameraBlend(MeshComp,CurrentCamera,BlendValue);
}

void UAnimNotifyState_LockCameraAnim::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime,EventReference);

	if (bLockCamera)
	{
		if (Camera)
		{
			if (AActor* InActor = Cast<AActor>(MeshComp->GetOuter()))
			{
				if (ISimpleAttackInterface* InAttackInterface = Cast<ISimpleAttackInterface>(InActor))
				{
					FVector TargetPointLocation = InAttackInterface->GetTargetPointLocation();

					FRotator Rot = UKismetMathLibrary::FindLookAtRotation(
						Camera->GetActorLocation(),
						TargetPointLocation);

					if (InActor->GetWorld() && InActor->GetWorld()->GetFirstPlayerController())
					{
						InActor->GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(Rot);
					}
				}
			}
		}
	}
}

void UAnimNotifyState_LockCameraAnim::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation,EventReference);

	if (bReturn)
	{
		if (AActor* InActor = Cast<AActor>(MeshComp->GetOuter()))
		{
			if (InActor->GetWorld() && InActor->GetWorld()->GetFirstPlayerController())
			{
				if (InActor->GetWorld()->GetFirstPlayerController()->GetPawn())
				{
					InActor->GetWorld()->GetFirstPlayerController()->Possess(InActor->GetWorld()->GetFirstPlayerController()->GetPawn());
				}
			}
		}
	}
}

AActor* UAnimNotifyState_LockCameraAnim::GetBlendCamera(USkeletalMeshComponent* MeshComp, const FName & InCameraString)
{
	if (MeshComp->GetOwner())
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(MeshComp->GetOwner()->GetWorld(), ACameraActor::StaticClass(), OutActors);

		for (auto& Tmp : OutActors)
		{
			if (Tmp->ActorHasTag(InCameraString))
			{
				return Tmp;
			}
		}
	}

	return nullptr;
}

void UAnimNotifyState_LockCameraAnim::CameraBlend(USkeletalMeshComponent* MeshComp, const FName& InCameraString, float InBlendValue)
{
	Camera = GetBlendCamera(MeshComp,InCameraString);

	if (Camera && MeshComp->GetOuter())
	{
		if (APlayerController* InPlayerController = MeshComp->GetOuter()->GetWorld()->GetFirstPlayerController())
		{
			InPlayerController->SetViewTargetWithBlend(Camera, InBlendValue,(EViewTargetBlendFunction)TargetBlendFunction);
		}
	}
}