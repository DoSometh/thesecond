// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleGrabLockComponent.h"
#include "MotionControllerComponent.h"
#include "Interface/VRGrabInterface.h"
#include "Components/SimpleGrabComponent.h"
#include "Core/SimpleVRFeatureKitMethod.h"

USimpleGrabLockComponent::USimpleGrabLockComponent()
	:RotatorOffset(90.f, 0.f, 0.f)
	,GrabSpeed(20.f)
	,GrabTolerance(2.f)
{
	PrimaryComponentTick.bCanEverTick = true;

	ShapeColor = FColor(0, 0, 255, 255);
}

// Called when the game starts
void USimpleGrabLockComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &USimpleGrabLockComponent::OnGrabBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &USimpleGrabLockComponent::OnGrabEndOverlap);
}

// Called every frame
void USimpleGrabLockComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TickTask(DeltaTime);
}

void USimpleGrabLockComponent::TickTask(float DeltaTime)
{
	if (SimpleGrabLockInfo.IsValid() &&
		GetAttachParent())
	{
		if (SimpleGrabLockInfo.BGrabInterface->IsGrab())
		{
			if (SimpleGrabLockInfo.GrabLockState != ESimpleGrabLockState::GRABLOCK_LOCK)
			{
				FAttachmentTransformRules AttachmentTransformRules(
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::KeepWorld,
					true);

				if (AActor* InBActor = Cast<AActor>(SimpleGrabLockInfo.BGrabInterface))
				{
					InBActor->GetRootComponent()->AttachToComponent(
						this,
						AttachmentTransformRules);

					SimpleGrabLockInfo.GrabLockState = ESimpleGrabLockState::GRABLOCK_LOCK;

					//提醒上层锁住握住
					SimpleGrabLockInfo.BGrabInterface->LockGrab(this);
				}
				else
				{
					check(0);
				}
			}
			else
			{
				FVector ActorStart = SimpleGrabLockInfo.AGrabInterface->GetMotionController()->GetComponentLocation();
				FVector ActorTaget = SimpleGrabLockInfo.BGrabInterface->GetMotionController()->GetComponentLocation();

				SimpleVRFeatureKitMethod::GrabLock(
					ActorStart,
					ActorTaget,
					RotatorOffset,
					SimpleGrabLockInfo.AGrabInterface->GetMotionController());
			}
		}
		else
		{
			if (SimpleVRFeatureKitMethod::Lerp(
				SimpleGrabLockInfo.BGrabInterface->GetMotionController(),
				Cast<AActor>(SimpleGrabLockInfo.BGrabInterface)->GetRootComponent(),
				DeltaTime,
				GrabSpeed,
				GrabTolerance))
			{
				if (SimpleGrabLockInfo.GrabLockState == ESimpleGrabLockState::GRABLOCK_LOCK)
				{
					if (AActor* InAttachTopChildren = Cast<AActor>(SimpleGrabLockInfo.BGrabInterface))
					{
						FAttachmentTransformRules AttachmentTransformRules(
							EAttachmentRule::SnapToTarget,
							EAttachmentRule::SnapToTarget,
							EAttachmentRule::KeepWorld,
							true);

						InAttachTopChildren->GetRootComponent()->AttachToComponent(
							SimpleGrabLockInfo.BGrabInterface->GetMotionController(),
							AttachmentTransformRules);

						SimpleGrabLockInfo.AGrabInterface->GetMotionController()->SetWorldRotation(FRotator::ZeroRotator);
						SimpleGrabLockInfo.BGrabInterface->GetMotionController()->SetWorldRotation(FRotator::ZeroRotator);
					}

					SimpleGrabLockInfo.BGrabInterface->EndLockGrab();

					SimpleGrabLockInfo.Clear();
				}
			}
		}
	}
}

AActor* USimpleGrabLockComponent::GetAttachTopChildren()
{
	auto& InAttachChildren = GetAttachChildren();
	if (InAttachChildren.Num() > 0)
	{
		return InAttachChildren[0]->GetOwner();
	}

	return NULL;
}

AActor* USimpleGrabLockComponent::GetAttachObject()
{
	if (GetOwner())
	{
		auto& InAttachChildren = GetOwner()->GetRootComponent()->GetAttachChildren();
		for (auto& Tmp : InAttachChildren)
		{
			if (USimpleGrabComponent* InGrabComponent = Cast<USimpleGrabComponent>(Tmp))
			{
				return InGrabComponent->GetAttachObject();
			}
		}
	}

	return NULL;
}

void USimpleGrabLockComponent::OnGrabBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IVRGrabInterface* InBVRGrabInterface = Cast<IVRGrabInterface>(OtherActor))
	{
		if (IVRGrabInterface* InAVRGrabInterface = Cast<IVRGrabInterface>(GetAttachObject()))//已经被抓取了
		{
			if (InBVRGrabInterface != InAVRGrabInterface)
			{
				if (!SimpleGrabLockInfo.IsValid())
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnGrabBeginOverlap"));
					}

					InBVRGrabInterface->StartLockGrab();

					SimpleGrabLockInfo.AGrabInterface = InAVRGrabInterface;
					SimpleGrabLockInfo.BGrabInterface = InBVRGrabInterface;

					SimpleGrabLockInfo.GrabLockState = ESimpleGrabLockState::GRABLOCK_TOUCH;
				}
			}
		}
	}
}

void USimpleGrabLockComponent::OnGrabEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IVRGrabInterface* InBVRGrabInterface = Cast<IVRGrabInterface>(OtherActor))
	{
		if (IVRGrabInterface* InAVRGrabInterface = Cast<IVRGrabInterface>(GetAttachObject()))//已经被抓取了
		{
			if (InBVRGrabInterface != InAVRGrabInterface)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("OnGrabEndOverlap"));
				}

				InBVRGrabInterface->EndLockGrab();

				if (SimpleGrabLockInfo.IsValid())
				{
					if (SimpleGrabLockInfo.GrabLockState == ESimpleGrabLockState::GRABLOCK_TOUCH)
					{
						SimpleGrabLockInfo.Clear();
					}
				}
			}
		}
	}
}