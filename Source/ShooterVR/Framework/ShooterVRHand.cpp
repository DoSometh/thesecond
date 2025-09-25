// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterVRHand.h"
#include "../ShooterVRType.h"
#include "Components/SkeletalMeshComponent.h"
#include "MotionControllerComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SimpleGrabComponent.h"
#include "Components/SimpleSliderComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "ShooterVRCharacter.h"
#include "ShooterVRGameStateBase.h"
#include "SimpleVRFeatureKitLibrary.h"
#include "ShooterVR/Weapon/Core/VRWeaponBase.h"

AShooterVRHand::AShooterVRHand()
{
	VRSystem = CreateDefaultSubobject<USceneComponent>(TEXT("VRSystem"));
	RootComponent = VRSystem;

	HandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandMesh"));
	HandMesh->SetupAttachment(RootComponent);

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("SplineInstance"));
	Spline->SetupAttachment(VRSystem);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);

	HandType = EVRHandType::VR_RIGHT;
	HeldComponent = NULL;
	GrabRadius = 6.f;
	DragDistance = 650.f;
	CurvilinearDegree = 200.f;
	bDragDebugSphere = true;
	DragSubsection = 10;
	LastAllowHitObject = NULL;
	DragAxisValue = 25.f;
	bPrepareDrag = false;
	DragTarget = NULL;
	bDrag = false;
	bGrab = false;
	bEnableSliderTrace = false;
	SliderComponent = NULL;

	RefMotionController = NULL;
}

void AShooterVRHand::InitShooterVRHand(UMotionControllerComponent* InMotionController)
{
	//��ʼ��
	RefMotionController = InMotionController;

	if (HandType == EVRHandType::VR_LEFT)
	{
		FVector HandScale3D = HandMesh->GetRelativeScale3D();
		HandScale3D.Z *=-1.f;

		HandMesh->SetRelativeScale3D(HandScale3D);
	}
}

void AShooterVRHand::Grab(UMotionControllerComponent* InMotionController)
{
	bGrab = true;

	if (!bDrag)
	{
		if (bEnableSliderTrace)
		{
			if (USimpleSliderComponent* InSliderComponent = GetSliderComponentOverlapMotionController(InMotionController->GetComponentLocation()))
			{
				SliderComponent = InSliderComponent;

				SliderComponent->SetGrab(true);

				SliderComponent->SetInitializeDragPosition(GetMotionControllerSliderLocation(InMotionController));
				SliderComponent->SetInitializeDragRotator(InMotionController->GetComponentRotation());

				//�ֻ�������������
				FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::KeepWorld, true);
				GetRootComponent()->AttachToComponent(SliderComponent, AttachmentTransformRules);

				return;
			}
		}
	}

	if (!HeldComponent)
	{
		Pickup(InMotionController);
	}
	else
	{
		bool bDefault = true;
		if (USimpleGrabComponent* NewHeldComponent = GetGrabComponentNearMotionController(InMotionController->GetComponentLocation()))
		{
			if (NewHeldComponent->IsHeld())
			{
				bDefault = false;

				SwapAndOtherHand(NewHeldComponent);
			}
		}

		if (bDefault)
		{
			if (HeldComponent->GetGrabType() == EGrabType::GRAB_SNAP)
			{
				if (HeldComponent->TryRelease())
				{
					HeldComponent = nullptr;
				}
			}
		}
	}
}

void AShooterVRHand::TryRelease()
{
	bGrab = false;

	if (SliderComponent)
	{
		//��ԭ�ֵ�MotionController��
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
		GetRootComponent()->AttachToComponent(RefMotionController, AttachmentTransformRules);

		SliderComponent->SetGrab(false);
		SliderComponent = nullptr;
	}
	else if (HeldComponent)
	{
		if (HeldComponent->GetGrabType() != EGrabType::GRAB_SNAP)
		{
			Release();
		}
	}
}

bool AShooterVRHand::Release()
{
	if (HeldComponent->TryRelease())
	{
		HeldComponent = nullptr;
		return true;
	}

	return false;
}

void AShooterVRHand::Drag(UMotionControllerComponent* InMotionController)
{
	if (AShooterVRCharacter* InVRCharacter = Cast<AShooterVRCharacter>(GetOwner()))
	{
		FVector StartPosition = InMotionController->GetComponentLocation();
		FVector ForwardVector = InMotionController->GetForwardVector();

		FVector EndPosition = StartPosition + ForwardVector * DragDistance;

		FHitResult OutHit;
		TArray<FVector> OutPathPositions;

		ETraceTypeQuery TraceTypeQuery = ETraceTypeQuery::TraceTypeQuery1;
		TArray<AActor*> ActorsToIgnore;

		EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;
		if (bDragDebugSphere)
		{
			DrawDebugType = EDrawDebugTrace::ForOneFrame;
		}

		float DrawDebugTime = 0.f;
		ActorsToIgnore.Add(this);

		UKismetSystemLibrary::LineTraceSingle(
			GetWorld(),
			StartPosition,
			EndPosition,
			TraceTypeQuery,
			true,//bTraceComplex
			ActorsToIgnore,
			DrawDebugType,
			OutHit,
			true);//bIgnoreSelf

		if (OutHit.bBlockingHit)
		{
			TArray<USimpleGrabComponent*> Components;
			if (USimpleVRFeatureKitLibrary::GetSimpleGrabComponentsByActor(OutHit.GetActor(), Components))
			{
				bPrepareDrag = true;
				DragTarget = OutHit.GetActor();

				if (LastAllowHitObject != DragTarget)
				{
					LastAllowHitObject = DragTarget;

					//���� ѡ����
					USimpleVRFeatureKitLibrary::PlayHapticEffect(ChoiceFeedbackEffect, InMotionController);
				}

				FVector HitLocation = OutHit.GetActor()->GetActorLocation();
				Spline->SetLocationAtSplinePoint(0, HitLocation, ESplineCoordinateSpace::World);
				Spline->SetLocationAtSplinePoint(1, StartPosition, ESplineCoordinateSpace::World);

				Spline->SetRotationAtSplinePoint(1, InMotionController->GetComponentRotation(), ESplineCoordinateSpace::Local);

				float Distance = FVector::Distance(StartPosition, HitLocation);

				FVector TargetDir = HitLocation - StartPosition;
				TargetDir.Normalize();

				float Percentage = 1.f - FVector::DotProduct(ForwardVector, TargetDir);

				DragTangent = FVector(-Percentage * Distance * CurvilinearDegree, 0.f, -Percentage * Distance * CurvilinearDegree * 2.f);

				Spline->SetTangentsAtSplinePoint(1, DragTangent, DragTangent, ESplineCoordinateSpace::World);

				//�ռ���������
				{
					float DistanceAlongSpline = Spline->GetSplineLength();
					float DistanceIncrement = DistanceAlongSpline / (float)DragSubsection;

					for (int32 i = DragSubsection; i > 0; i--)
					{
						float MergeDistance = DistanceIncrement * i;

						FVector PointLocation = Spline->GetLocationAtDistanceAlongSpline(
							MergeDistance,
							ESplineCoordinateSpace::World);

						if (bDragDebugSphere)
						{
							::DrawDebugSphere(GetWorld(), PointLocation, 3.5f, 12, FColor::Green, false, 0.f);
						}

						OutPathPositions.Add(PointLocation);
					}
				}
			}
			else
			{
				DrawArrayPointLine(StartPosition, EndPosition, OutPathPositions);
			}
		}
		else
		{
			DrawArrayPointLine(StartPosition, EndPosition, OutPathPositions);
		}

		//������Ч
		InVRCharacter->SetTeleportTraceNiagaraVisibility(true);
		InVRCharacter->SetUserCurvePointArray(OutPathPositions);
	}
}

void AShooterVRHand::DragEnd()
{
	if (AShooterVRCharacter* InVRCharacter = Cast<AShooterVRCharacter>(GetOwner()))
	{
		InVRCharacter->SetTeleportTraceNiagaraVisibility(false);
	}

	bPrepareDrag = false;
	DragTarget = NULL;
}

void AShooterVRHand::Pickup(UMotionControllerComponent* InMotionController)
{
	if (USimpleGrabComponent* NewHeldComponent = GetGrabComponentNearMotionController(InMotionController->GetComponentLocation()))
	{
		if (NewHeldComponent->IsHeld())
		{
			MoveItem(NewHeldComponent);
		}
		else
		{
			NewHeldComponent->TryGrab(InMotionController, this);

			SetHeldComponent(NewHeldComponent);
		}
	}
}

void AShooterVRHand::MoveItem(USimpleGrabComponent* InNewHeldComponent)
{
	if (AShooterVRHand* InOtherHand = Cast<AShooterVRHand>(InNewHeldComponent->GetAttachObject()))
	{
		if (InNewHeldComponent->TryRelease())
		{
			InOtherHand->ClearHeldComponent();

			InNewHeldComponent->TryGrab(RefMotionController, this);

			SetHeldComponent(InNewHeldComponent);
		}
	}
}

void AShooterVRHand::SwapAndOtherHand(USimpleGrabComponent* InBNewHeldComponent)
{
	USimpleGrabComponent* InANewHeldComponent = HeldComponent;

	if (AShooterVRHand* InOtherHand = Cast<AShooterVRHand>(InBNewHeldComponent->GetAttachObject()))
	{
		InBNewHeldComponent->TryRelease();

		//�ͷ��Լ���
		InANewHeldComponent->TryRelease();

		//����
		InBNewHeldComponent->TryGrab(RefMotionController, this);
		InANewHeldComponent->TryGrab(InOtherHand->GetMotionController(), InOtherHand);

		//���ø��Ե�ʰȡ���
		SetHeldComponent(InBNewHeldComponent);
		InOtherHand->SetHeldComponent(InANewHeldComponent);
	}
}

void AShooterVRHand::ClearHeldComponent()
{
	HeldComponent = NULL;
}

void AShooterVRHand::SetHeldComponent(USimpleGrabComponent* InNewHeldComponent)
{
	HeldComponent = InNewHeldComponent;
}

void AShooterVRHand::DrawArrayPointLine(const FVector& InStart, const FVector& InEnd, TArray<FVector>& OutVector)
{
	FVector StartToEndDistance = InEnd - InStart;
	FVector DistanceIncrement = StartToEndDistance * (1.f / (float)DragSubsection);

	OutVector.Add(InStart);
	for (size_t i = 1; i < (DragSubsection - 1); i++)
	{
		OutVector.Add(InStart + DistanceIncrement * i);
	}
	OutVector.Add(InEnd);
}

bool AShooterVRHand::TraceItemComponents(
	const FVector& InMotionControllerLocation,
	TFunction<bool(const FHitResult&)> InFun)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery4);

	TArray<AActor*> ActorsToIgnore;
	EDrawDebugTrace::Type DrawDebugType = EDrawDebugTrace::None;

	if (bDragDebugSphere)
	{
		DrawDebugType = EDrawDebugTrace::ForDuration;
	}

	FHitResult OutHit;

	if (UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		InMotionControllerLocation,
		InMotionControllerLocation,
		GrabRadius,
		ObjectTypes,
		false,
		ActorsToIgnore,
		DrawDebugType,
		OutHit,
		true))
	{
		return InFun(OutHit);
	}

	return false;
}

USimpleSliderComponent* AShooterVRHand::GetSliderComponentOverlapMotionController(const FVector& InMotionControllerLocation)
{
	USimpleSliderComponent* LocalSliderComponent = nullptr;

	if (TraceItemComponents(InMotionControllerLocation,
		[&](const FHitResult& InResult)-> bool
		{
			if (InResult.GetActor())
			{
				TArray<UActorComponent*> SliderComponents;
				InResult.GetActor()->GetComponents(USimpleSliderComponent::StaticClass(), SliderComponents);
			
				if (SliderComponents.Num())
				{
					LocalSliderComponent = Cast<USimpleSliderComponent>(SliderComponents[0]);
					return true;
				}
			}

			return false;
		}))
	{
		return LocalSliderComponent;
	}

	return NULL;
}

USimpleGrabComponent* AShooterVRHand::FindLatelyGrabComponentByClass(
	const FVector& InMotionControllerLocation, 
	TArray<UActorComponent*> GrabComponents,
	UClass* InExcludeParentObjectClass)
{
	USimpleGrabComponent* LocalNearestGrabComponent = nullptr;

	float Distance = 999999999.f;
	for (auto& Tmp : GrabComponents)
	{
		if (Tmp != HeldComponent)
		{
			if (USimpleGrabComponent* InSimpleGrabComponent = Cast<USimpleGrabComponent>(Tmp))
			{
				//�ų��ĸ������
				if (InExcludeParentObjectClass)
				{
					if (InSimpleGrabComponent->GetOwner() &&
						InSimpleGrabComponent->GetOwner()->GetAttachParentActor() &&
						InSimpleGrabComponent->GetOwner()->GetAttachParentActor()->IsA(InExcludeParentObjectClass))
					{
						continue;
					}
				}

				float TmpDistance = FVector::Distance(InSimpleGrabComponent->GetComponentLocation(), InMotionControllerLocation);
				if (TmpDistance < Distance)
				{
					Distance = TmpDistance;
					LocalNearestGrabComponent = InSimpleGrabComponent;
				}
			}
		}
	}

	return LocalNearestGrabComponent;
}

USimpleGrabComponent* AShooterVRHand::GetGrabComponentNearMotionController(const FVector& InMotionControllerLocation)
{
	USimpleGrabComponent* LocalNearestGrabComponent = nullptr;

	if (TraceItemComponents(InMotionControllerLocation,
		[&](const FHitResult& InResult)-> bool
		{
			if (InResult.GetActor())
			{
				TArray<UActorComponent*> GrabComponents;
				InResult.GetActor()->GetComponents(USimpleGrabComponent::StaticClass(), GrabComponents);

			
				LocalNearestGrabComponent = FindLatelyGrabComponentByClass(
					InMotionControllerLocation,
					GrabComponents,
					AVRWeaponBase::StaticClass());

				return LocalNearestGrabComponent != NULL;
			}

			return false;
		}))
	{
		return LocalNearestGrabComponent;
	}

	return NULL;
}

bool AShooterVRHand::IsDragAction()
{
	FRotator CurrentRotator = GetActorRotation();
	float RollValue = FMath::Abs(LastRotator.Roll - CurrentRotator.Roll);

	LastRotator = CurrentRotator;

	return RollValue > DragAxisValue;
}

//
void AShooterVRHand::BeginPlay()
{
	Super::BeginPlay();

}

void AShooterVRHand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (RefMotionController)
	{
		//
		if (IsDragAction())
		{
			if (bPrepareDrag)
			{
				if (DragTarget)
				{
					bPrepareDrag = false;

					//
					USimpleVRFeatureKitLibrary::PlayHapticEffect(DragFeedbackEffect, RefMotionController);

					// if (AShooterVRGameStateBase* InGameState = GetWorld()->GetGameState<AShooterVRGameStateBase>())
					// {
					// 	InGameState->VRDragManage.SubmitCommand(DragTarget, this, DragTangent, &bDrag);
					// }
				}
			}
		}

		//��ק�������������ǽ���ʰȡ
		if (bGrab && bDrag)
		{
			if (!HeldComponent)
			{
				Pickup(RefMotionController);
			}
		}

		//��ק�����е�Slider
		if (!bDrag && bGrab)
		{
			if (SliderComponent)
			{
				SliderComponent->SetDragPosition(GetMotionControllerSliderLocation());
				SliderComponent->SetDragRotator(RefMotionController->GetComponentRotation());
			}
		}
	}
}

FVector AShooterVRHand::GetMotionControllerSliderLocation(UMotionControllerComponent* InMotionController)
{
	if (SliderComponent)
	{
		UMotionControllerComponent* InMotionControllerComponent = NULL;
		if (InMotionController)
		{
			InMotionControllerComponent = InMotionController;
		}
		else
		{
			InMotionControllerComponent = RefMotionController;
		}

		if (InMotionControllerComponent)
		{
			FVector FinalLocation = GetTransform().InverseTransformPosition(InMotionControllerComponent->GetComponentLocation());
			FinalLocation = FVector(FinalLocation.Y, FinalLocation.X, FinalLocation.Z);

			return FinalLocation;
		}
	}

	return FVector::ZeroVector;
}
