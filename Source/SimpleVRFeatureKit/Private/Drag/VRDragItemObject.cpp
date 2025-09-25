// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Drag/VRDragItemObject.h"
#include "Drag/VRDragItemType.h"
#include "Components/SplineComponent.h"
#include "Settings/SimpleVRFeatureKitSettings.h"
#include "SimpleVRFeatureKitLibrary.h"
#include "Components/SimpleGrabComponent.h"
#include "Interface/VRFeatureKitDragInterface.h"
#include "SimpleVRFeatureKitType.h"

FVRDragItemObject::FVRDragItemObject()
	:DragState(EVRItemObjectState::VR_DRAG_FREE)
	,EndObject(NULL)
	,StartObject(NULL)
	,Time(0.f)
{
	EndPoint = FVector::ZeroVector;
	bTraceObject = NULL;
}

void FVRDragItemObject::Tick(float DeltaTime)
{
	if (!IsFree())
	{
		if (Spline && EndObject && StartObject)
		{
			Time += DeltaTime;

			float Velocity = GetDefault<USimpleVRFeatureKitSettings>()->DragVelocity;
			float Distance = Time * Velocity;

			FVector Location = Spline->GetWorldLocationAtDistanceAlongSpline(Distance);
			FRotator Rotator = Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
		
			//玩家有没有一瞬间抓住物品
			bool bHeld = false;
			if (USimpleGrabComponent* InGrabComponent = USimpleVRFeatureKitLibrary::GetSimpleGrabComponentByActor(StartObject))
			{
				bHeld = InGrabComponent->IsHeld();
			}

			if ((EndPoint - Location).Size() <= 0.f || bHeld)
			{
				if (IVRFeatureKitDragInterface* InDragInterface = Cast<IVRFeatureKitDragInterface>(StartObject))
				{
					InDragInterface->OnEndDraged();
				}

				OnDragItemCompleteDelegate.ExecuteIfBound();

				if (bTraceObject)
				{
					*bTraceObject = false;
				}

				bTraceObject = NULL;
				EndObject = nullptr;
				StartObject = nullptr;
				DragState = EVRItemObjectState::VR_DRAG_FREE;
				EndPoint = FVector::ZeroVector;
			}
			//绘制用户开启的debug
			else if(GetDefault<USimpleVRFeatureKitSettings>()->bDrawDrag)
			{
				int32 DragSubsection = GetDefault<USimpleVRFeatureKitSettings>()->DragSubsection;

				float DistanceAlongSpline = Spline->GetSplineLength();
				float DistanceIncrement = DistanceAlongSpline / (float)DragSubsection;

				for (int32 i = DragSubsection; i > 0; i--)
				{
					float MergeDistance = DistanceIncrement * i;

					FVector PointLocation = Spline->GetLocationAtDistanceAlongSpline(
						MergeDistance,
						ESplineCoordinateSpace::World);

					::DrawDebugSphere(
						EndObject->GetWorld(),
						PointLocation, 
						GetDefault<USimpleVRFeatureKitSettings>()->SphereRadius,
						GetDefault<USimpleVRFeatureKitSettings>()->SphereSegments,
						GetDefault<USimpleVRFeatureKitSettings>()->SphereColor,
						false,
						0.f);
				}
			}

			if (StartObject)
			{
				StartObject->SetActorLocationAndRotation(
					Location,
					Rotator,
					false,
					nullptr,
					TeleportFlagToEnum(true));
			}
		}
	}
}

void FVRDragItemObject::Init(AActor* InStart, USceneComponent* InEnd, const FVector& InTangentsValue, bool* bTrace, FSimpleDelegate InDragItemCompleteDelegate)
{
	OnDragItemCompleteDelegate = InDragItemCompleteDelegate;

	if (bTrace)
	{
		*bTrace = true;
		bTraceObject = bTrace;
	}

	if (IVRFeatureKitDragInterface* InDragInterface = Cast<IVRFeatureKitDragInterface>(InStart))
	{
		InDragInterface->OnStartDraged();
	}

	DragState = EVRItemObjectState::VR_DRAG_BUSY;

	StartObject = InStart;
	EndObject = InEnd;
	Time = 0.f;
	EndPoint = EndObject->GetComponentLocation();

	Spline = NewObject<USplineComponent>(InEnd);
	Spline->RegisterComponent();

	Spline->SetLocationAtSplinePoint(0, StartObject->GetActorLocation(), ESplineCoordinateSpace::World);
	Spline->SetLocationAtSplinePoint(1, EndObject->GetComponentLocation(), ESplineCoordinateSpace::World);

	Spline->SetTangentsAtSplinePoint(1, InTangentsValue * 3.f, InTangentsValue * 3.f, ESplineCoordinateSpace::World);
}

bool FVRDragItemObject::IsFree() const
{
	return DragState == EVRItemObjectState::VR_DRAG_FREE;
}