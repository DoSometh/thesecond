//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotify/AnimNotify_PlayAnimMontage.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"

UAnimNotify_PlayAnimMontage::UAnimNotify_PlayAnimMontage()
{
    PlayRate = 1.f;
}

FString UAnimNotify_PlayAnimMontage::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_PlayAnimMontage::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    if (Animation)
    {
        if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
        {
            if (UAnimMontage *InTempMontage = Cast<UAnimMontage>(Animation))
            {
                //InCharacter->StopAnimMontage(InTempMontage);

                float MontageDuration = InCharacter->PlayAnimMontage(InTempMontage,PlayRate,SlotName);

                if (MontageDuration > 0.f)
                {
                    UE_LOG(LogTemp, Log, TEXT("Montage is playing successfully."));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to play montage."));
                }
            }   
        }
    }
}