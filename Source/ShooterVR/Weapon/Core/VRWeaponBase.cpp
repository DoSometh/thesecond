// Fill out your copyright notice in the Description page of Project Settings.
#include "VRWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SimpleGrabComponent.h"
#include "../../AbilitiesSystem/VRAbilitySystemComponent.h"
#include "../../Components/GameFramework/FightComponent.h"
#include "../../Framework/ShooterVRGameStateBase.h"
#include "Animation/AnimInstance.h"

AVRWeaponBase::AVRWeaponBase()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	RootComponent = WeaponMesh;

	GrabComponent = CreateDefaultSubobject<USimpleGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(RootComponent);

	GrabComponent->SetGrabType(EGrabType::GRAB_SNAP);
	WeaponMesh->SetSimulatePhysics(true);

	//GAS初始化
	AbilitySystemComponent = CreateDefaultSubobject<UVRAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	FightComponent = CreateDefaultSubobject<UFightComponent>(TEXT("FightComponent"));
	FightComponent->SetIsReplicated(true);

	ID = INDEX_NONE;
}

FGameplayAbilitySpecHandle AVRWeaponBase::RegisterGameplayAbility(const TSubclassOf<UGameplayAbility>& InGameplayAbility)
{
	return FightComponent->RegisterGameplayAbility(InGameplayAbility);
}

bool AVRWeaponBase::UnregisterGameplayAbility(const FGameplayAbilitySpecHandle& InHandle)
{
	return FightComponent->UnregisterGameplayAbility(InHandle);
}

bool AVRWeaponBase::ExecuteGameplayAbility(const FGameplayAbilitySpecHandle& InHandle)
{
	return FightComponent->ExecuteGameplayAbility(InHandle);
}

void AVRWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	GrabComponent->GrabDelegate.AddDynamic(this, &AVRWeaponBase::Grab);
	GrabComponent->ReleaseDelegate.AddDynamic(this, &AVRWeaponBase::Release);

	//注册
	AbilitySystemComponent->AbilityActorInfo->AnimInstance = WeaponMesh->GetAnimInstance();
	AbilitySystemComponent->AbilityActorInfo->SkeletalMeshComponent = WeaponMesh;
}

void AVRWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVRWeaponBase::Grab()
{

}

void AVRWeaponBase::Release()
{

}

void AVRWeaponBase::RegistrationAttribute()
{
	//具体数据，从DataTable里面将数据注册到 Attributes
	if (AShooterVRGameStateBase* InGameStateBase = GetWorld()->GetGameState<AShooterVRGameStateBase>())
	{
		InGameStateBase->RegistrationAFrameworkCharacter(this);
	}
}

UAbilitySystemComponent* AVRWeaponBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

AActor* AVRWeaponBase::GetAttachObject() const
{
	return GrabComponent->GetAttachObject();
}

bool AVRWeaponBase::IsHeld() const
{
	return GrabComponent->IsHeld();
}

APawn* AVRWeaponBase::GetCaster()
{
	return Cast<APawn>(GetAttachParentActor());
}

void AVRWeaponBase::ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect)
{
	if (FightComponent)
	{
		FightComponent->ExecuteGameplayEffect(InGameplayEffect);
	}
}

void AVRWeaponBase::PlayAnimMontage(UAnimMontage* InMontage)
{
	if (WeaponMesh)
	{
		if (WeaponMesh->GetAnimInstance())
		{
			WeaponMesh->GetAnimInstance()->Montage_Play(InMontage);
		}
	}
}

void AVRWeaponBase::StopAnimMontage()
{
	if (WeaponMesh)
	{
		if (WeaponMesh->GetAnimInstance())
		{
			WeaponMesh->GetAnimInstance()->StopAllMontages(0.f);
		}
	}
}
