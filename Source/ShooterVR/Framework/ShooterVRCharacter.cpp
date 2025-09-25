// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterVRCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"
#include "../Actor/VRTeleportVisualizer.h"
#include "NavigationSystem.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "../ShooterVRType.h"
#include "ShooterVRHand.h"
#include "Components/ArrowComponent.h"
#include "../AbilitiesSystem/VRAbilitySystemComponent.h"
#include "../Components/GameFramework/FightComponent.h"

// Sets default values
AShooterVRCharacter::AShooterVRCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	VRSystem = CreateDefaultSubobject<USceneComponent>(TEXT("VRSystem"));
	VRSystem->SetupAttachment(RootComponent);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(VRSystem);

	ControllerRight = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("ControllerRight"));
	ControllerRight->SetupAttachment(VRSystem);
	ControllerRight->MotionSource = TEXT("Right");
	ControllerRight->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	ControllerLeft = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("ControllerLeft"));
	ControllerLeft->SetupAttachment(VRSystem);
	ControllerLeft->MotionSource = TEXT("Left");
	ControllerLeft->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//������Ч
	TeleportTraceNiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TeleportTraceNiagaraSystem"));
	TeleportTraceNiagaraSystem->SetupAttachment(VRSystem);

	SnapTurnDegrees = -30.f;
	LocalTeleportLaunchSpeed = 650.f;
	bTeleportTraceActive = false;
	bValidTeleportLocation = false;
	VRTeleportVisualizer = NULL;

	SetTeleportTraceNiagaraVisibility(bTeleportTraceActive);
}

void AShooterVRCharacter::SnapTurn(bool bRight)
{
	float LocalYawDelta = bRight ? FMath::Abs(SnapTurnDegrees) : SnapTurnDegrees;

	AddControllerYawInput(LocalYawDelta);
}

void AShooterVRCharacter::SpawnHand(EVRHandType InType)
{
	if (VRShooterHandClass)
	{
		UMotionControllerComponent* MotionControllerComponent = (InType == EVRHandType::VR_RIGHT ? ControllerRight : ControllerLeft);
		AShooterVRHand *&InHand = (InType == EVRHandType::VR_RIGHT ? RightHand : LeftHand);

		//���ɾ����hand
		{
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = this;
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			InHand = GetWorld()->SpawnActor<AShooterVRHand>(VRShooterHandClass, ActorSpawnParameters);

			if (InHand)
			{
				InHand->HandType = InType;

				//����
				InHand->AttachToComponent(
					MotionControllerComponent,
					FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));

				//ִ�����������
				InHand->InitShooterVRHand(MotionControllerComponent);
			}
		}
	}
}

// Called when the game starts or when spawned
void AShooterVRCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (true)
	{
		SpawnHand(EVRHandType::VR_RIGHT);
		SpawnHand(EVRHandType::VR_LEFT);

		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Local);
	}
}

// Called every frame
void AShooterVRCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void AShooterVRCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AShooterVRCharacter::StartTeleportTrace()
{
	if (!bTeleportTraceActive)
	{
		bTeleportTraceActive = true;
		TeleportTraceNiagaraSystem->SetVisibility(bTeleportTraceActive);

		if (VRTeleportVisualizerClass)
		{
			//����VRTeleportVisualizer
			FActorSpawnParameters ActorSpawnParameters;
			ActorSpawnParameters.Owner = this;
			ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			VRTeleportVisualizer = GetWorld()->SpawnActor<AVRTeleportVisualizer>(VRTeleportVisualizerClass,ActorSpawnParameters);
		}
	}
}

void AShooterVRCharacter::TeleportTrace()
{
	FVector StartPosition = ControllerRight->GetComponentLocation();
	FVector ForwardVector = ControllerRight->GetForwardVector();

	FHitResult OutHit;
	TArray<FVector> OutPathPositions;
	FVector OutLastTraceDestination;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
	float DrawDebugTime = 0.f;

	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery1);
	ActorsToIgnore.Add(this);

	//��ȡ�����ߵ����߼������������
	UGameplayStatics::Blueprint_PredictProjectilePath_ByObjectType(
		GetWorld(),
		OutHit,
		OutPathPositions,
		OutLastTraceDestination,
		StartPosition,
		ForwardVector * LocalTeleportLaunchSpeed,
		true,
		3.5f,
		ObjectTypes,
		false,
		ActorsToIgnore,
		DrawDebugType,
		DrawDebugTime);

	OutPathPositions.Insert(StartPosition, 0);

	if (OutHit.bBlockingHit)
	{
		//������㴫�ݵ�Niagara����
		SetUserCurvePointArray(OutPathPositions);

		bValidTeleportLocation = UNavigationSystemV1::K2_ProjectPointToNavigation(
			GetWorld(),
			OutHit.Location,
			ProjectedLocation,
			nullptr,
			nullptr);

		VRTeleportVisualizer->GetRootComponent()->SetVisibility(bValidTeleportLocation);

		if (bValidTeleportLocation)
		{			
			if (VRTeleportVisualizer)
			{
				ProjectedLocation.Z -= 8.f;
				VRTeleportVisualizer->SetActorLocation(ProjectedLocation);
			}
		}	
	}
}

void AShooterVRCharacter::EndTeleportTrace()
{
	if (bTeleportTraceActive)
	{
		bTeleportTraceActive = false;
		SetTeleportTraceNiagaraVisibility(bTeleportTraceActive);

		if (VRTeleportVisualizer)
		{
			VRTeleportVisualizer->Destroy();
			VRTeleportVisualizer = nullptr;
		}
	}
}

void AShooterVRCharacter::TryTeleport()
{
	if (bValidTeleportLocation)
	{
		bValidTeleportLocation = false;

		ProjectedLocation.Z += GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
		FRotator ActorRotation = GetActorRotation();

		TeleportTo(ProjectedLocation, FRotator(0.f, ActorRotation.Yaw, 0.f), false, false);
	}
}

void AShooterVRCharacter::MoveForward(float Value)
{
	if ((FollowCamera != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = FollowCamera->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AShooterVRCharacter::MoveRight(float Value)
{
	if ((FollowCamera != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = FollowCamera->GetComponentRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AShooterVRCharacter::GrabLeftPressed()
{
	if (LeftHand)
	{
		LeftHand->Grab(ControllerLeft);
	}
}

void AShooterVRCharacter::GrabLeftReleased()
{
	if (LeftHand)
	{
		LeftHand->TryRelease();
	}
}

void AShooterVRCharacter::GrabRightPressed()
{
	if (RightHand)
	{
		RightHand->Grab(ControllerRight);
	}
}

void AShooterVRCharacter::GrabRightReleased()
{
	if (RightHand)
	{
		RightHand->TryRelease();
	}
}

void AShooterVRCharacter::LeftDrag()
{
	if (LeftHand)
	{
		LeftHand->Drag(ControllerLeft);
	}
}

void AShooterVRCharacter::LeftDragEnd()
{
	if (LeftHand)
	{
		LeftHand->DragEnd();
	}
}

void AShooterVRCharacter::RightDrag()
{
	if (RightHand)
	{
		RightHand->Drag(ControllerRight);
	}
}

void AShooterVRCharacter::RightDragEnd()
{
	if (RightHand)
	{
		RightHand->DragEnd();
	}
}

void AShooterVRCharacter::SetUserCurvePointArray(const TArray<FVector>& InPointArray)
{
	if (TeleportTraceNiagaraSystem)
	{
		static FName UserPointArray = TEXT("User.PointArray");
		UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(
			TeleportTraceNiagaraSystem,
			UserPointArray,
			InPointArray);
	}
}

void AShooterVRCharacter::SetTeleportTraceNiagaraVisibility(bool bVisibility)
{
	if (TeleportTraceNiagaraSystem)
	{
		TeleportTraceNiagaraSystem->SetVisibility(bVisibility);
	}
}