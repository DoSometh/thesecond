// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleAttachComponent.h"
#include "Interface/VRFeatureKitInterface.h"
#include "Core/SimpleVRFeatureKitMethod.h"

USimpleAttachComponent::USimpleAttachComponent()
	:ID(INDEX_NONE)
	,AttachSpeed(10.f)
	,TmpAttachObject(NULL)
{
	PrimaryComponentTick.bCanEverTick = true;

	AttachTolerance = 2.f;

	LastTmpAttachObject = NULL;

	ShapeColor = FColor(255,0,0,255);
}

void USimpleAttachComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &USimpleAttachComponent::OnAttachBeginOverlap);
	OnComponentEndOverlap.AddDynamic(this, &USimpleAttachComponent::OnAttachEndOverlap);
}

AActor* USimpleAttachComponent::GetCurrentAttachVRKitInterface() const
{
	auto VRKitAttachChildren = GetAttachChildren();
	if (VRKitAttachChildren.Num() > 0)
	{
		if (IVRFeatureKitInterface* InKitInterface = Cast<IVRFeatureKitInterface>(VRKitAttachChildren[0]->GetOwner()))
		{
			return Cast<AActor>(InKitInterface);
		}
	}

	return nullptr;
}

void USimpleAttachComponent::OnAttachBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IVRFeatureKitInterface* InVRFeatureKitInterface = Cast<IVRFeatureKitInterface>(OtherActor))
	{
		if (LastTmpAttachObject != OtherActor)
		{
			if (!GetCurrentAttachVRKitInterface() && //当前没有附加对象
				!TmpAttachObject.IsValid())//临时附加对象为空
			{
				if (InVRFeatureKitInterface->IsValidAttachID())
				{
					if (InVRFeatureKitInterface->GetVRFeatureKitID() == ID)
					{
						//对方释放对方的Attach 
						InVRFeatureKitInterface->TryRelease();

						//开始准备Lerp动画
						TmpAttachObject = OtherActor;

						AttachDynamicDelegate.Broadcast(this, EAttachInfoType::PREPARING_INSTALLATION);
					}
					else
					{
						AttachDynamicDelegate.Broadcast(this, EAttachInfoType::INCORRECT_TYPE);
					}
				}
				else
				{
					AttachDynamicDelegate.Broadcast(this, EAttachInfoType::ID_INVALID);
				}
			}
			else
			{
				AttachDynamicDelegate.Broadcast(this, EAttachInfoType::ALREADY_EQUIPPED);
			}
		}
	}
}

void USimpleAttachComponent::OnAttachEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (LastTmpAttachObject == OtherActor)
	{
		if (IVRFeatureKitInterface* InKitInterface = Cast<IVRFeatureKitInterface>(LastTmpAttachObject))
		{
			InKitInterface->OnEndAttached();
		}

		LastTmpAttachObject = NULL;
	}
}

void USimpleAttachComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TmpAttachObject.IsValid())
	{
		if (!GetCurrentAttachVRKitInterface())
		{
			if (SimpleVRFeatureKitMethod::Lerp(
				this,
				TmpAttachObject->GetRootComponent(),
				DeltaTime,
				AttachSpeed,
				AttachTolerance))
			{
				FAttachmentTransformRules AttachmentTransformRules(
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::SnapToTarget,
					EAttachmentRule::KeepWorld,
					true);

				TmpAttachObject->GetRootComponent()->AttachToComponent(
					this,
					AttachmentTransformRules);

				if (IVRFeatureKitInterface* InKitInterface = Cast<IVRFeatureKitInterface>(TmpAttachObject))
				{
					InKitInterface->OnAttached();
				}

				LastTmpAttachObject = TmpAttachObject;
				TmpAttachObject = NULL;

				AttachDynamicDelegate.Broadcast(this,EAttachInfoType::INSTALLED);
			}
		}
	}
}