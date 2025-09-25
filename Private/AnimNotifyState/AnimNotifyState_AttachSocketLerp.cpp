//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotifyState/AnimNotifyState_AttachSocketLerp.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleComboType.h"
#include "Components/SkeletalMeshComponent.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "Kismet/GameplayStatics.h"

//ֻ�ܵ�������ʹ��
struct FAttachSocketLerpTmpData :public FInternallyInterpolatedStructureTmpData
{
	TWeakObjectPtr<AActor> AttachActor;
	TWeakObjectPtr<USceneComponent> Mesh;
};

TMap<int32, FAttachSocketLerpTmpData> AttachSocketLerpPools;

UAnimNotifyState_AttachSocketLerp::UAnimNotifyState_AttachSocketLerp()
	:Super()
{

}

void UAnimNotifyState_AttachSocketLerp::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (AttachSocketLerpPools.Contains(InCharacter->GetUniqueID()))
		{
			AttachSocketLerpPools.Remove(InCharacter->GetUniqueID());
		}

		FAttachSocketLerpTmpData& InArmTmpData = AttachSocketLerpPools.Add(InCharacter->GetUniqueID());
		InArmTmpData.NotifyStateTotalDuration = TotalDuration;

		if (ISimpleComboInterface *InComboInterface = Cast<ISimpleComboInterface>(InCharacter))
		{
			InArmTmpData.AttachActor = InComboInterface->AttachSocketLerpActor();
		}
		
		if (InArmTmpData.AttachActor.IsValid())
		{
			if (MeshComp->ComponentTags.Contains(MeshTag))
			{
				InArmTmpData.Mesh = MeshComp;
			}
			else
			{
				if (USceneComponent* InSceneComponent = InCharacter->FindComponentByTag<USceneComponent>(MeshTag))
				{
					InArmTmpData.Mesh = InSceneComponent;
				}
			}

			if (InArmTmpData.Mesh.IsValid())
			{
				FDetachmentTransformRules TransformRules(EDetachmentRule::KeepWorld, false);
				InArmTmpData.AttachActor->DetachFromActor(TransformRules);
			}
		}
	}
}

void UAnimNotifyState_AttachSocketLerp::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (AActor* InOnwerActor = Cast<AActor>(MeshComp->GetOuter()))
	{
		if (AttachSocketLerpPools.Contains(InOnwerActor->GetUniqueID()))
		{
			float InValue = AttachSocketLerpPools[InOnwerActor->GetUniqueID()].GetValue(FrameDeltaTime);

			TWeakObjectPtr<AActor> AttachActor = AttachSocketLerpPools[InOnwerActor->GetUniqueID()].AttachActor;
			TWeakObjectPtr<USceneComponent> Mesh = AttachSocketLerpPools[InOnwerActor->GetUniqueID()].Mesh;

			if (AttachActor.IsValid() && 
				Mesh.IsValid())
			{
				FTransform OriginalLocation = Mesh->GetSocketTransform(SocketNameOriginal);
				FTransform TargetLocation = Mesh->GetSocketTransform(SocketNameTarget);

				FTransform NewTmpTransform;
				NewTmpTransform.Blend(OriginalLocation, TargetLocation, InValue);
				NewTmpTransform.SetScale3D(FVector(1.f));

				AttachActor->SetActorTransform(NewTmpTransform);
			}
		}
	}
}

void UAnimNotifyState_AttachSocketLerp::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (AttachSocketLerpPools.Contains(InCharacter->GetUniqueID()))
		{
			TWeakObjectPtr<AActor> AttachActor = AttachSocketLerpPools[InCharacter->GetUniqueID()].AttachActor;
			TWeakObjectPtr<USceneComponent> Mesh = AttachSocketLerpPools[InCharacter->GetUniqueID()].Mesh;

			if (AttachActor.IsValid() && Mesh.IsValid())
			{
				FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, true);
				AttachActor->AttachToComponent(Mesh.Get(), TransformRules, SocketNameTarget);
			}

			AttachSocketLerpPools.Remove(InCharacter->GetUniqueID());
		}	
	}
}