#include "VRClipBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SimpleGrabComponent.h"
#include "../../Framework/ShooterVRHand.h"
#include "ShooterVR/Actor/SimulationModel.h"
#include "GameplayEffect.h"
#include "Kismet/GameplayStatics.h"

AVRClipBase::AVRClipBase()
	:Super()
{
	ClipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ClipMesh"));
	RootComponent = ClipMesh;

	GrabComponent = CreateDefaultSubobject<USimpleGrabComponent>(TEXT("GrabComponent"));
	GrabComponent->SetupAttachment(RootComponent);

	GrabComponent->SetGrabType(EGrabType::GRAB_SNAP);
	ClipMesh->SetSimulatePhysics(true);

	ID = INDEX_NONE;
	BulletNumber = 10;
}

void AVRClipBase::BeginPlay()
{
	Super::BeginPlay();
}

void AVRClipBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ASimulationModel* AVRClipBase::SpawnUsedBulletModel(const FVector& InLocation, const FRotator& InRotation)
{
	return SpawnSimulationModel(UsedBulletModelClass, InLocation, InRotation);
}

void AVRClipBase::StartSelfDestruction()
{
	SetLifeSpan(10.f);
}

void AVRClipBase::PlayInstallSound()
{
	UGameplayStatics::PlaySoundAtLocation(
		GetWorld(),
		InstallSoundCue,
		GetActorLocation(),
		FRotator::ZeroRotator,
		1, 1, 0.f,
		SoundAttenuation);
}

AActor* AVRClipBase::GetAttachObject() const
{
	return GrabComponent->GetAttachObject();
}

bool AVRClipBase::TryRelease()
{
	//存在手的话 要释放
	if (AShooterVRHand* InHand = Cast<AShooterVRHand>(GetAttachObject()))
	{
		return InHand->Release();
	}
	else
	{
		return GrabComponent->TryRelease();
	}
}

ASimulationModel* AVRClipBase::SpawnBulletModel(const FVector& InLocation, const FRotator& InRotation)
{
	return SpawnSimulationModel(BulletModelClass, InLocation, InRotation);
}

ASimulationModel* AVRClipBase::SpawnSimulationModel(TSubclassOf<ASimulationModel> InCalss, const FVector& InLocation, const FRotator& InRotation)
{
	if (InCalss)
	{
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;
		ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		if (ASimulationModel* InSimulationModel = GetWorld()->SpawnActor<ASimulationModel>(
			InCalss,
			InLocation,
			InRotation,
			ActorSpawnParameters))
		{
			return InSimulationModel;
		}
	}

	return NULL;
}