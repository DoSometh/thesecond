//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "Hit/ComboSkillHitCapsule.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AHitCapsuleCollision::AHitCapsuleCollision(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	HitDamage = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitDamage"));
	HitDamage->SetupAttachment(RootComponent);
}

UPrimitiveComponent* AHitCapsuleCollision::GetHitDamage()
{
	return HitDamage;
}

void AHitCapsuleCollision::SetCapsuleHalfHeight(float InNewCapsuleHalfHeight)
{
	HitDamage->SetCapsuleHalfHeight(InNewCapsuleHalfHeight);
}

void AHitCapsuleCollision::SetCapsuleRadius(float InNewCapsuleRadius)
{
	HitDamage->SetCapsuleRadius(InNewCapsuleRadius);
}
// Called when the game starts or when spawned
void AHitCapsuleCollision::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AHitCapsuleCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitCapsuleCollision::StartHandleDamage_Inner(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	FHitResult OutHitResult;

	if (!bFromSweep)
	{
		if (bEnableSweep)
		{
			if (!IsExitIgnoredActor(OtherActor))
			{
				OutHitResult = SweepResult;

				//¿ªÊ¼BoxÉäÏß¼ì²â
				const FVector StartTraceLocation = HitDamage->GetComponentLocation();
				const FVector EndTraceLocation = StartTraceLocation;
				const float Radius = HitDamage->GetScaledCapsuleRadius();
				const float HalfHeight = HitDamage->GetScaledCapsuleHalfHeight();

				TArray<AActor*> ActorsToIgnore;
				GetIgnoreTraceActor(ActorsToIgnore);

				if (UKismetSystemLibrary::CapsuleTraceSingle(
					GetWorld(),
					StartTraceLocation,
					EndTraceLocation,
					Radius,
					HalfHeight,
					TraceTypeQuery,
					false,
					ActorsToIgnore,
					(EDrawDebugTrace::Type)DrawDebugTrace,
					OutHitResult, true))
				{
					bFromSweep = true;
				}
			}
		}
	}

	Super::StartHandleDamage_Inner(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, bFromSweep ? OutHitResult : SweepResult);
}

FVector AHitCapsuleCollision::GetExtent() const
{
	if (HitDamage)
	{
		return FVector(
			HitDamage->GetScaledCapsuleRadius(),
			HitDamage->GetScaledCapsuleHalfHeight(),
			HitDamage->GetScaledCapsuleHalfHeight_WithoutHemisphere());
	}

	return Super::GetExtent();
}