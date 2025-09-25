#include "AnimNotify/AnimNotify_Throw.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SimpleComboType.h"
#include "Components/SkeletalMeshComponent.h"
#include "CombatInterface/SimpleCombatInterface.h"
#include "SimpleCombatBPLibrary.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

UAnimNotify_Throw::UAnimNotify_Throw()
{
	ImpulseValue = 1000.f;
}

FString UAnimNotify_Throw::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Throw::Notify(
	USkeletalMeshComponent* MeshComp,
	UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (AActor* InCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		//需要找到真正被驱动的角色
		USkeletalMeshComponent* InNewMeshComponent = nullptr;
		if (!SubMeshTagName.IsNone())
		{
			InNewMeshComponent = InCharacter->FindComponentByTag<USkeletalMeshComponent>(SubMeshTagName);
		}

		if (!InNewMeshComponent)
		{
			InNewMeshComponent = MeshComp;
		}

		//找到被附加的
		const TArray<TObjectPtr<USceneComponent>> Childrens = InNewMeshComponent->GetAttachChildren();

		ACharacter* GarbCharacter = nullptr;
		for (auto& Tmp : Childrens)
		{
			if (ACharacter* InHitBox = Cast<ACharacter>(Tmp->GetOwner()))
			{
				if (InHitBox != InCharacter)
				{
					GarbCharacter = InHitBox;
					break;
				}	
			}
		}

		if (GarbCharacter)
		{
			GarbCharacter->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, false));
			GarbCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Falling);
			GarbCharacter->GetCharacterMovement()->GravityScale = 1.f;

			FVector ActorForwardVector = InCharacter->GetActorForwardVector();

			FVector Impulse = ActorForwardVector * ImpulseValue;
			GarbCharacter->GetCharacterMovement()->AddImpulse(Impulse, true);

			if (ISimpleComboInterface *InComboInterface = Cast<ISimpleComboInterface>(GarbCharacter))
			{
				InComboInterface->Throw(InCharacter);
			}
		}
	}
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif