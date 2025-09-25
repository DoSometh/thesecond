// Fill out your copyright notice in the Description page of Project Settings.
#include "VRShooterAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "../../DataTable/Attribute/CharacterAttributeTable.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "../../Framework/Core/FrameworkCharacterBase.h"

UVRShooterAttributeSet::UVRShooterAttributeSet()
	:Super()
	,Health(100.f)
	,MaxHealth(100.f)
	,Mana(100.f)
	,MaxMana(100.f)
	,PhysicsDefense(5.f)
	,MagicDefense(5.f)
{

}

void UVRShooterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRShooterAttributeSet, Health, OldValue,
		TEXT("OnRep_Health Error"));
}

void UVRShooterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRShooterAttributeSet, MaxHealth, OldValue,
		TEXT("OnRep_MaxHealth Error"));
}

void UVRShooterAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRShooterAttributeSet, Mana, OldValue,
		TEXT("OnRep_Mana Error"));
}

void UVRShooterAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRShooterAttributeSet, MaxMana, OldValue,
		TEXT("OnRep_MaxMana Error"));
}

void UVRShooterAttributeSet::OnRep_PhysicsDefense(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRShooterAttributeSet, PhysicsDefense, OldValue,
		TEXT("OnRep_PhysicsDefense Error"));
}

void UVRShooterAttributeSet::OnRep_MagicDefense(const FGameplayAttributeData& OldValue)
{
	CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(
		UVRShooterAttributeSet, MagicDefense, OldValue,
		TEXT("OnRep_MagicDefense Error"));
}

void UVRShooterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UVRShooterAttributeSet, Health);
	DOREPLIFETIME(UVRShooterAttributeSet, MaxHealth);
	DOREPLIFETIME(UVRShooterAttributeSet, Mana);
	DOREPLIFETIME(UVRShooterAttributeSet, MaxMana);
	DOREPLIFETIME(UVRShooterAttributeSet, PhysicsDefense);
	DOREPLIFETIME(UVRShooterAttributeSet, MagicDefense);
};

void UVRShooterAttributeSet::GetSourceCharacterAndSourceActor(
	UAbilitySystemComponent* SourceAbilitySystemComponent,
	AActor*& InSourceActor,
	AFrameworkCharacterBase*& InSourceCharacter)
{
	if (SourceAbilitySystemComponent)
	{
		InSourceActor = SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		AController* SourceController = SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();
		if (SourceController == NULL && InSourceActor != NULL)
		{
			if (APawn* InPawn = Cast<APawn>(InSourceActor))
			{
				SourceController = InPawn->GetController();
			}
			else if(APawn *InParentPawn = Cast<APawn>(InSourceActor->GetAttachParentActor()))//VR 
			{
				SourceController = InParentPawn->GetController();
			}
		}

		if (SourceController)
		{
			InSourceCharacter = Cast<AFrameworkCharacterBase>(SourceController->GetPawn());
		}
		else
		{
			InSourceCharacter = Cast<AFrameworkCharacterBase>(InSourceActor);
		}
	}
}

void UVRShooterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* SourceAbilitySystemComponent = Context.GetOriginalInstigatorAbilitySystemComponent();

	const FGameplayTagContainer& SourceTagContainer = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
	AFrameworkCharacterBase* Target = Data.Target.AbilityActorInfo.IsValid() ? Cast<AFrameworkCharacterBase>(Data.Target.AbilityActorInfo->AvatarActor) : NULL;

	float Magnitude = 0.f;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		Magnitude = Data.EvaluatedData.Magnitude;
	}

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		if (Target && Magnitude < 0.f)
		{
			AFrameworkCharacterBase* SourceCharacter = NULL;
			AActor* SourceActor = NULL;
			GetSourceCharacterAndSourceActor(SourceAbilitySystemComponent, SourceActor, SourceCharacter);

			Target->HandleHealth(SourceCharacter, SourceActor, SourceTagContainer, Magnitude);
		}
	}
}

bool UVRShooterAttributeSet::PreGameplayEffectExecute(struct FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UVRShooterAttributeSet::RegistrationProperties(const FAttributeDataTableBase* InData)
{
	Super::RegistrationProperties(InData);

	const FCharacterAttributeTable* InTable = (const FCharacterAttributeTable*)InData;

	RegistrationParam(Health, InTable->Health);
	RegistrationParam(MaxHealth, InTable->Health);
	RegistrationParam(Mana, InTable->Mana);
	RegistrationParam(MaxMana, InTable->Mana);
	RegistrationParam(PhysicsDefense, InTable->PhysicsDefense);
	RegistrationParam(MagicDefense, InTable->MagicDefense);
}