//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Abilities/Cue/Actor/GameplayCueNotify_Effects.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "NiagaraComponent.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

AGameplayCueNotify_Effects::AGameplayCueNotify_Effects()
	:bAttach(false)
	,AttachLocation(EAttachLocation::KeepWorldPosition)
{

}

void AGameplayCueNotify_Effects::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters)
{
	if (DurationName.IsValid() && 
		MyTarget && 
		IsValid(MyTarget) &&
		GetWorld())
	{
		switch (EventType)
		{
			case EGameplayCueEvent::OnActive:
			case EGameplayCueEvent::Executed:
			{
				if (EmitterTemplate)
				{
					UParticleSystemComponent* InParticleSystemComponent = NULL;
					if (bAttach)
					{
						InParticleSystemComponent = UGameplayStatics::SpawnEmitterAttached(
							EmitterTemplate,
							MyTarget->GetRootComponent(), 
							AttachPointName,
							MyTarget->GetActorLocation() + MyTarget->GetActorForwardVector() * PositionOffset,
							MyTarget->GetActorRotation() + RotatorOffset, //
							MyTarget->GetActorScale(),
							AttachLocation);
					}
					else
					{
						FTransform Transform = MyTarget->GetActorTransform();

						Transform.SetLocation(Transform.GetLocation() + MyTarget->GetActorForwardVector() * PositionOffset);
						Transform.SetRotation((Transform.GetRotation().Rotator() + RotatorOffset).Quaternion());

						InParticleSystemComponent = UGameplayStatics::SpawnEmitterAtLocation(
							GetWorld(),
							EmitterTemplate, Transform);
					}

					if (InParticleSystemComponent)
					{
						InParticleSystemComponent->SetFloatParameter(
							DurationName,
							Parameters.RawMagnitude);
					}
				}
				else if (NiagaraTemplate)
				{
					UNiagaraComponent* InNiagaraComponent = NULL;
					if (bAttach)
					{
						InNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
							NiagaraTemplate,
							MyTarget->GetRootComponent(),
							AttachPointName,
							MyTarget->GetActorLocation() + MyTarget->GetActorForwardVector() * PositionOffset,
							MyTarget->GetActorRotation() + RotatorOffset,
							AttachLocation,
							true);
					}
					else
					{
						InNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
							GetWorld(),
							NiagaraTemplate, 
							MyTarget->GetActorLocation() + MyTarget->GetActorForwardVector() * PositionOffset,
							MyTarget->GetActorRotation() + RotatorOffset);
					}

					if (InNiagaraComponent)
					{
						InNiagaraComponent->SetFloatParameter(
							DurationName,
							Parameters.RawMagnitude);
					}
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