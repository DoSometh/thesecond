// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Components/SimpleTouchControlComponent.h"
#include "Core/SimpleVRFeatureKitMethod.h"

USimpleTouchControlComponent::USimpleTouchControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SpawnDefaultHumanChainIncremental();

	IncrementSpringbackType = EIncrementSpringbackType::CONTROLCHAIN_RESTORE;

	LHand.Add(TEXT("hand_l"));
	LHand.Add(TEXT("lowerarm_l"));
	LHand.Add(TEXT("upperarm_l"));

	RHand.Add(TEXT("hand_r"));
	RHand.Add(TEXT("lowerarm_r"));
	RHand.Add(TEXT("upperarm_r"));
}

FSimpleTouchControlIncremental* USimpleTouchControlComponent::FindTouchControlIncremental(FName BoneName)
{
	for (auto &Tmp : ChainIncrementalMap)
	{
		if (Tmp.Value.Bones.Contains(BoneName))
		{
			return &Tmp.Value;
		}
	}

	return NULL;
}

FTouchControlHandle USimpleTouchControlComponent::StartTouch(FName BoneName, USceneComponent* InController)
{
	if (!BoneName.IsNone())
	{
		//处理胳膊抓握
		{
			if (LHand.Contains(BoneName))
			{
				BoneName = TEXT("hand_l");
			}
			else if (RHand.Contains(BoneName))
			{
				BoneName = TEXT("hand_r");
			}
		}

		check(InController);

		FTouchControlHandle InHandle = SpawnUniqueHandle();
		TouchControlInfoPool.Add(InHandle, FSimpleTouchControlInfo());
		TouchControlInfoPool[InHandle].TouchController = InController;

		TouchControlInfoPool[InHandle].BoneName = BoneName;
		TouchControlInfoPool[InHandle].InitializationPosition = GetOwner()->GetTransform().InverseTransformPosition(InController->GetComponentLocation());
		TouchControlInfoPool[InHandle].InitializationRotation = InController->GetComponentRotation().GetInverse();

		if (FSimpleTouchControlIncremental *InIncremental = FindTouchControlIncremental(BoneName))
		{
			TouchControlInfoPool[InHandle].IncrementalPtr = InIncremental;

			InIncremental->ReferenceCount++;
		}

		return InHandle;
	}

	return INDEX_NONE;
 }

void USimpleTouchControlComponent::EndTouch(FTouchControlHandle InHandle)
{
	if (FSimpleTouchControlInfo *InControlInfo = TouchControlInfoPool.Find(InHandle))
	{
		if (InControlInfo->IncrementalPtr)
		{
			InControlInfo->IncrementalPtr->ReferenceCount--;
		}
	}

	TouchControlInfoPool.Remove(InHandle);
}

FTouchControlHandle USimpleTouchControlComponent::SpawnUniqueHandle() const
{
	FTouchControlHandle ControlHandle = FMath::RandRange(-99999,99999);

	if (!TouchControlInfoPool.Contains(ControlHandle) && ControlHandle != INDEX_NONE)
	{
		return ControlHandle;
	}

	return SpawnUniqueHandle();
}

void USimpleTouchControlComponent::BeginPlay()
{
	Super::BeginPlay();


}

void USimpleTouchControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType, ThisTickFunction);

	TArray<int32> RemoveHandle;

	//更新抓住的骨骼
	for (auto &Tmp: TouchControlInfoPool)
	{
		if (!Tmp.Value.BoneName.IsNone())
		{
			if (Tmp.Value.TouchController.IsValid() && Tmp.Value.IncrementalPtr)
			{
				FVector RelativeOwnerPosition = GetOwner()->GetTransform().InverseTransformPosition(Tmp.Value.TouchController->GetComponentLocation());
				Tmp.Value.IncrementalPtr->IncrementPosition = RelativeOwnerPosition - Tmp.Value.InitializationPosition;

				if (Tmp.Value.BoneName == Tmp.Value.IncrementalPtr->MainBoneName)
				{
					Tmp.Value.IncrementalPtr->IncrementRotation = Tmp.Value.TouchController->GetComponentRotation().GetInverse() - Tmp.Value.InitializationRotation;
				}

				//限制
				Tmp.Value.IncrementalPtr->IncrementPosition = SimpleVRFeatureKitMethod::Clamp(Tmp.Value.IncrementalPtr->IncrementPosition, Tmp.Value.IncrementalPtr->MinPosition, Tmp.Value.IncrementalPtr->MaxPosition);
				Tmp.Value.IncrementalPtr->IncrementRotation = SimpleVRFeatureKitMethod::Clamp(Tmp.Value.IncrementalPtr->IncrementRotation, Tmp.Value.IncrementalPtr->MinRotation, Tmp.Value.IncrementalPtr->MaxRotation);
			}	
			else
			{
				RemoveHandle.Add(Tmp.Key);
			}
		}
	}

	//防止错误
	for (auto &Tmp : RemoveHandle)
	{
		TouchControlInfoPool.Remove(Tmp);
	}

	//所有链都包含
	for (auto &Tmp : ChainIncrementalMap)
	{
		if (Tmp.Value.ReferenceCount == 0)
		{
			//判定还原
			switch (IncrementSpringbackType)
			{
				case EIncrementSpringbackType::CONTROLCHAIN_RESTORE:
				{
					if (!SimpleVRFeatureKitMethod::IsNearlyEqual(Tmp.Value.IncrementPosition, FVector::ZeroVector, 1.0f) ||
						!SimpleVRFeatureKitMethod::IsNearlyEqual(Tmp.Value.IncrementRotation, FRotator::ZeroRotator,1.0f))
					{
						Tmp.Value.IncrementPosition = FMath::Lerp(Tmp.Value.IncrementPosition, FVector::ZeroVector, DeltaTime * 10.f);
						Tmp.Value.IncrementRotation = FMath::Lerp(Tmp.Value.IncrementRotation, FRotator::ZeroRotator, DeltaTime * 10.f);
					}

					break;
				}
				case EIncrementSpringbackType::CONTROLCHAIN_SPRING_RESTORE:
				{
					break;
				}
				case EIncrementSpringbackType::CONTROLCHAIN_NO_RESTORE:
				{
					break;
				}
			}
		}
	}
}

void USimpleTouchControlComponent::SpawnDefaultHumanChainIncremental()
{
	for (uint8 i = 0; i < (uint8)EMainTouchControlChain::CONTROLCHAIN_MAX; i++)
	{
		ChainIncrementalMap.Add(i,FSimpleTouchControlIncremental());

		FSimpleTouchControlIncremental &InTouchControlIncremental = ChainIncrementalMap[i];
	
		switch ((EMainTouchControlChain)i)
		{
			case EMainTouchControlChain::CONTROLCHAIN_HAND_R:
			{
				InTouchControlIncremental.MainBoneName = "hand_r";
				InTouchControlIncremental.Bones.Add("hand_r");

				InTouchControlIncremental.Bones.Add("index_01_r");
				InTouchControlIncremental.Bones.Add("index_02_r");
				InTouchControlIncremental.Bones.Add("index_03_r");

				InTouchControlIncremental.Bones.Add("middle_01_r");
				InTouchControlIncremental.Bones.Add("middle_02_r");
				InTouchControlIncremental.Bones.Add("middle_03_r");

				InTouchControlIncremental.Bones.Add("pinky_01_r");
				InTouchControlIncremental.Bones.Add("pinky_02_r");
				InTouchControlIncremental.Bones.Add("pinky_03_r");

				InTouchControlIncremental.Bones.Add("ring_01_r");
				InTouchControlIncremental.Bones.Add("ring_02_r");
				InTouchControlIncremental.Bones.Add("ring_03_r");

				InTouchControlIncremental.Bones.Add("thumb_01_r");
				InTouchControlIncremental.Bones.Add("thumb_02_r");
				InTouchControlIncremental.Bones.Add("thumb_03_r");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_HAND_L:
			{
				InTouchControlIncremental.MainBoneName = "hand_l";
				InTouchControlIncremental.Bones.Add("hand_l");

				InTouchControlIncremental.Bones.Add("index_01_l");
				InTouchControlIncremental.Bones.Add("index_02_l");
				InTouchControlIncremental.Bones.Add("index_03_l");

				InTouchControlIncremental.Bones.Add("middle_01_l");
				InTouchControlIncremental.Bones.Add("middle_02_l");
				InTouchControlIncremental.Bones.Add("middle_03_l");

				InTouchControlIncremental.Bones.Add("pinky_01_l");
				InTouchControlIncremental.Bones.Add("pinky_02_l");
				InTouchControlIncremental.Bones.Add("pinky_03_l");

				InTouchControlIncremental.Bones.Add("ring_01_l");
				InTouchControlIncremental.Bones.Add("ring_02_l");
				InTouchControlIncremental.Bones.Add("ring_03_l");

				InTouchControlIncremental.Bones.Add("thumb_01_l");
				InTouchControlIncremental.Bones.Add("thumb_02_l");
				InTouchControlIncremental.Bones.Add("thumb_03_l");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_LEG_R:
			{
				InTouchControlIncremental.MainBoneName = "foot_r";
				InTouchControlIncremental.Bones.Add("thigh_r");
				InTouchControlIncremental.Bones.Add("foot_r");
				InTouchControlIncremental.Bones.Add("ball_r");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_LEG_L:
			{
				InTouchControlIncremental.MainBoneName = "foot_l";
				InTouchControlIncremental.Bones.Add("thigh_l");
				InTouchControlIncremental.Bones.Add("foot_l");
				InTouchControlIncremental.Bones.Add("ball_l");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_HEAD:
			{
				InTouchControlIncremental.MainBoneName = "head";
				InTouchControlIncremental.Bones.Add("neck_01");
				InTouchControlIncremental.Bones.Add("head");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_PELVIS:
			{
				InTouchControlIncremental.MainBoneName = "pelvis";
				InTouchControlIncremental.Bones.Add("pelvis");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_UPPERARM_L:
			{
				InTouchControlIncremental.MainBoneName = "upperarm_l";
				InTouchControlIncremental.Bones.Add("upperarm_l");
				InTouchControlIncremental.Bones.Add("clavicle_l");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_UPPERARM_R:
			{
				InTouchControlIncremental.MainBoneName = "upperarm_r";
				InTouchControlIncremental.Bones.Add("upperarm_r");
				InTouchControlIncremental.Bones.Add("clavicle_r");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_LOWERARM_L:
			{
				InTouchControlIncremental.MainBoneName = "lowerarm_l";
				InTouchControlIncremental.Bones.Add("lowerarm_l");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_LOWERARM_R:
			{
				InTouchControlIncremental.MainBoneName = "lowerarm_r";
				InTouchControlIncremental.Bones.Add("lowerarm_r");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_SPINE_01:
			{
				InTouchControlIncremental.MainBoneName = "spine_01";
				InTouchControlIncremental.Bones.Add("spine_01");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_SPINE_02:
			{
				InTouchControlIncremental.MainBoneName = "spine_02";
				InTouchControlIncremental.Bones.Add("spine_02");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_SPINE_03:
			{
				InTouchControlIncremental.MainBoneName = "spine_03";
				InTouchControlIncremental.Bones.Add("spine_03");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_CALF_R:
			{
				InTouchControlIncremental.MainBoneName = "calf_r";
				InTouchControlIncremental.Bones.Add("calf_r");
				break;
			}
			case EMainTouchControlChain::CONTROLCHAIN_CALF_L:
			{
				InTouchControlIncremental.MainBoneName = "calf_l";
				InTouchControlIncremental.Bones.Add("calf_l");
				break;
			}
		}
	}
}

TMap<uint8, FSimpleTouchControlIncremental>* USimpleTouchControlComponent::GetChainIncrementalMap()
{ 
	return &ChainIncrementalMap;
}

