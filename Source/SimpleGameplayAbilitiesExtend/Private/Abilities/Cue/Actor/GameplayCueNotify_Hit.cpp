//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "Abilities/Cue/Actor/GameplayCueNotify_Hit.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AGameplayCueNotify_Hit::AGameplayCueNotify_Hit()
	:Super()
{

}

void AGameplayCueNotify_Hit::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	if (MyTarget && 
		IsValid(MyTarget) &&
		GetWorld())
	{
		switch (EventType)
		{
			case EGameplayCueEvent::Executed:
			{
				if (HitEmitterTemplate)
				{
					UGameplayStatics::SpawnEmitterAtLocation(
						GetWorld(), 
						HitEmitterTemplate, MyTarget->GetActorTransform());
				}
				else if (HitNiagaraTemplate)
				{
					UNiagaraFunctionLibrary::SpawnSystemAtLocation(
						GetWorld(), 
						HitNiagaraTemplate, MyTarget->GetActorLocation());
				}
				break;
			}
		}
	}

	if (MyTarget)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("GetLocalRole = [%i]"), (int32)MyTarget->GetLocalRole()));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("EGameplayCueEvent = [%i]"), (int32)EventType));
	}

	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
}