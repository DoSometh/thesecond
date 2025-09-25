
#include "FrameworkCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "../../ShooterVRType.h"
#include "Components/ArrowComponent.h"
#include "../../AbilitiesSystem/VRAbilitySystemComponent.h"
#include "../../Components/GameFramework/FightComponent.h"
#include "../../Components/GameFramework/HealthComponent.h"
#include "../../AbilitiesSystem/AttributeSet/VRShooterAttributeSet.h"
#include "../ShooterVRGameStateBase.h"
#include "ShooterVR/DataRegistry/VRDataRegistryManage.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Components/DecalComponent.h"
#include "Animation/AnimInstance.h"

// Sets default values
AFrameworkCharacterBase::AFrameworkCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	//GAS��ʼ��
	AbilitySystemComponent = CreateDefaultSubobject<UVRAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	FightComponent = CreateDefaultSubobject<UFightComponent>(TEXT("FightComponent"));
	FightComponent->SetIsReplicated(true);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetIsReplicated(true);

	//һֱ����
	GetArrowComponent()->SetHiddenInGame(false);

	ID = INDEX_NONE;
	MainHitType = EVRHitType::VOICE_BULLET_STRIKE_HUMAN_BODY;

}

void AFrameworkCharacterBase::RegistrationAttribute()
{
	AttributeSet = const_cast<UVRShooterAttributeSet*>(AbilitySystemComponent->AddSet<UVRShooterAttributeSet>());

	//�������ݣ���DataTable���潫����ע�ᵽ Attributes
	if (AShooterVRGameStateBase* InGameStateBase = GetWorld()->GetGameState<AShooterVRGameStateBase>())
	{
		InGameStateBase->RegistrationAFrameworkCharacter(this);
	}
}

bool AFrameworkCharacterBase::IsDie() const
{
	return HealthComponent->IsDie();
}

// Called when the game starts or when spawned
void AFrameworkCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//ע������
	RegistrationAttribute();
}

// Called every frame
void AFrameworkCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFrameworkCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* AFrameworkCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

FGameplayAbilitySpecHandle AFrameworkCharacterBase::RegisterGameplayAbility(const TSubclassOf<UGameplayAbility>& InGameplayAbility)
{
	return FightComponent->RegisterGameplayAbility(InGameplayAbility);
}

bool AFrameworkCharacterBase::UnregisterGameplayAbility(const FGameplayAbilitySpecHandle& InHandle)
{
	return FightComponent->UnregisterGameplayAbility(InHandle);
}

bool AFrameworkCharacterBase::ExecuteGameplayAbility(const FGameplayAbilitySpecHandle& InHandle)
{
	return FightComponent->ExecuteGameplayAbility(InHandle);
}

void AFrameworkCharacterBase::HandleHealth(AFrameworkCharacterBase* InstigatorPawn,
	AActor* DamageCauser, const struct FGameplayTagContainer& InTags,
	float InNewValue)
{
	HealthComponent->HandleHealth(InstigatorPawn, DamageCauser, InTags, InNewValue);
}

void AFrameworkCharacterBase::PlayDie()
{
	BP_PlayDie();
}

void AFrameworkCharacterBase::PlayHit()
{
	PlayHitSound(MainHitType);
	PlayHitEffect(MainHitType);
	PlayHitScar(MainHitType);

	PlayBoneImpulse();

	BP_PlayHit();
}

void AFrameworkCharacterBase::ClearHitResult()
{
	HitResult.Reset();
}

void AFrameworkCharacterBase::PlayHitSound(EVRHitType InHitType)
{
	if (const FVoiceTable* InVoiceTable = FVRDataRegistryManage::Get()->FindVoiceCached(InHitType))
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			InVoiceTable->SoundCue,
			HitResult.Location,
			FRotator::ZeroRotator,
			1, 1, 0.f,
			InVoiceTable->SoundAttenuation);
	}
}

void AFrameworkCharacterBase::PlayHitEffect(EVRHitType InType)
{
	if (const FEffectTable* InEffectTable = FVRDataRegistryManage::Get()->FindEffectCached(InType))
	{
		if (InEffectTable->HitParticle)
		{
			FTransform SpawnTransform(HitResult.Location);
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				InEffectTable->HitParticle,
				SpawnTransform);
		}
		else if (InEffectTable->HitNiagara)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(
				GetWorld(),
				InEffectTable->HitNiagara,
				HitResult.Location, FRotator::ZeroRotator);
		}
	}
}

void AFrameworkCharacterBase::PlayHitScar(EVRHitType InType)
{
	if (const FEffectTable* InEffectTable = FVRDataRegistryManage::Get()->FindEffectCached(InType))
	{
		if (InEffectTable->Scar)
		{
			if (UMaterialInstanceDynamic* InstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(
				GetWorld(), InEffectTable->Scar))
			{
				InstanceDynamic->SetScalarParameterValue(FName(TEXT("Frame")), FMath::RandRange(0, 3));

				//x + yi
				FRotator DecalRotation = (HitResult.ImpactNormal * -1.f).ToOrientationRotator();
				DecalRotation.Roll = FMath::FRandRange(0.f, 360.f);

				if (UDecalComponent* InDecal = UGameplayStatics::SpawnDecalAttached(
					InstanceDynamic,
					InEffectTable->ScarSize,
					HitResult.GetComponent(),
					HitResult.BoneName,
					HitResult.ImpactPoint,
					DecalRotation,
					EAttachLocation::KeepWorldPosition,
					InEffectTable->ScarLifeSpan))
				{
					//�رվ��뵭�뵭��
					InDecal->SetFadeScreenSize(0.f);
				}
			}
		}
	}
}

bool AFrameworkCharacterBase::PlayBoneImpulse()
{
	if (!HitResult.BoneName.IsNone())
	{
		if (HitResult.BoneName != FName("pelvis"))
		{
			GetMesh()->SetAllBodiesBelowSimulatePhysics(HitResult.BoneName, true);
			GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(HitResult.BoneName, 1.0f);

			GetMesh()->AddImpulseToAllBodiesBelow((HitResult.ImpactNormal * -1.f) * 1000.f, HitResult.BoneName);
		
			// GThread::Get()->GetCoroutines().BindOnGoingLambda(0.19f, 
			// [&](float InRatio, float InIntervalTime, FName InBoneName)
			// {
			// 	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(InBoneName,FMath::Clamp(1.f - InRatio,0.f,1.f));
			// }, HitResult.BoneName);
			//
			// GThread::Get()->GetCoroutines().BindLambda(0.20f, 
			// [&](FName InBoneName)
			// {
			// 	GetMesh()->SetAllBodiesBelowSimulatePhysics(InBoneName, false);
			// 	GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(InBoneName, 0.0f);
			// }, HitResult.BoneName);

			return true;
		}
	}

	return false;
}

void AFrameworkCharacterBase::ExecuteGameplayEffect(const TSubclassOf<UGameplayEffect>& InGameplayEffect)
{
	if (FightComponent)
	{
		FightComponent->ExecuteGameplayEffect(InGameplayEffect);
	}
}

void AFrameworkCharacterBase::PlayAnimMontage(UAnimMontage* InMontage)
{
	if (GetMesh())
	{
		if (GetMesh()->GetAnimInstance())
		{
			GetMesh()->GetAnimInstance()->Montage_Play(InMontage);
		}
	}
}

void AFrameworkCharacterBase::StopAnimMontage()
{
	if (GetMesh())
	{
		if (GetMesh()->GetAnimInstance())
		{
			GetMesh()->GetAnimInstance()->StopAllMontages(0.f);
		}
	}
}
