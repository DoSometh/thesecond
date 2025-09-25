//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Abilities/ExecutionCalculation/ExecutionCalculation_0Velocity.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UExecutionCalculation_0Velocity::UExecutionCalculation_0Velocity()
{

}

void UExecutionCalculation_0Velocity::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* TargetAC = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAC = ExecutionParams.GetSourceAbilitySystemComponent();

	if (TargetAC)
	{
		if (ACharacter* InCharacter = Cast<ACharacter>(SourceAC->GetOwner()))
		{
			if (InCharacter->GetCharacterMovement())
			{
				InCharacter->GetCharacterMovement()->StopMovementImmediately();
			}
		}
	}	
}