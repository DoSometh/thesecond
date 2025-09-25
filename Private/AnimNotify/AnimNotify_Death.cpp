//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotify/AnimNotify_Death.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "PhysicsEngine/ConstraintInstance.h"

UAnimNotify_Death::UAnimNotify_Death()
{
	bEnableLiftTime = false;
	LifeTime = 10.f;
	bSimulation = false;

	ExcludeBoneName.Add(TEXT("upperarm_twist_01_r"));
	ExcludeBoneName.Add(TEXT("lowerarm_twist_01_r"));
	ExcludeBoneName.Add(TEXT("upperarm_twist_01_l"));
	ExcludeBoneName.Add(TEXT("lowerarm_twist_01_l"));
	ExcludeBoneName.Add(TEXT("thigh_twist_01_r"));
	ExcludeBoneName.Add(TEXT("calf_twist_01_r"));
	ExcludeBoneName.Add(TEXT("thigh_twist_01_l"));
	ExcludeBoneName.Add(TEXT("calf_twist_01_l"));
	ExcludeBoneName.Add(TEXT("neck_01"));
	ExcludeBoneName.Add(TEXT("Pulldown_joint1"));
	ExcludeBoneName.Add(TEXT("Pulldown_joint2"));
	ExcludeBoneName.Add(TEXT("Pulldown_joint3"));
	ExcludeBoneName.Add(TEXT("Pulldown_joint4"));
}

FString UAnimNotify_Death::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

bool UAnimNotify_Death::IsBoneBroken(USkeletalMeshComponent* MeshComp, FName BoneName) const
{
	// 获取所有约束实例
	const TArray<FConstraintInstance*>& Constraints = MeshComp->Constraints;

	// 遍历所有约束实例，检查是否与指定骨骼相关联并且断开
	for (const FConstraintInstance* Constraint : Constraints)
	{
		if (Constraint)
		{
			// 检查约束的骨骼名称是否匹配
			if (Constraint->ConstraintBone1 == BoneName || Constraint->ConstraintBone2 == BoneName)
			{
				// 检查约束是否断开
				if (Constraint->IsLinearBreakable() || Constraint->IsAngularBreakable())
				{
					return true; // 骨骼已经断开
				}
			}
		}
	}

	return false; // 骨骼没有断开
}

void UAnimNotify_Death::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ACharacter* InCharacter = Cast<ACharacter>(MeshComp->GetOuter()))
	{
		if (bEnableLiftTime)
		{
			InCharacter->SetLifeSpan(LifeTime);
		}

		if (bSimulation)
		{
			if (InCharacter->GetMesh())
			{
				// 启用布娃娃物理
				TArray<TObjectPtr<USceneComponent>> SceneChildern = InCharacter->GetMesh()->GetAttachChildren();
				SceneChildern.Add(InCharacter->GetMesh());
				
				//子类都开启模拟
				for (auto& Tmp : SceneChildern)
				{
					if (USkeletalMeshComponent *InSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Tmp))
					{
						TArray<FName> BoneNames;
						InSkeletalMeshComponent->GetBoneNames(BoneNames);

						InSkeletalMeshComponent->SetSimulatePhysics(true);
						InSkeletalMeshComponent->SetAllBodiesSimulatePhysics(true);
						//for (auto &SubTmp : BoneNames)
						//{
						//	if (!ExcludeBoneName.Contains(SubTmp))
						//	{
						//		InSkeletalMeshComponent->SetBodySimulatePhysics(SubTmp,true);
						//	}
						//	else
						//	{
						//		if (!IsBoneBroken(InSkeletalMeshComponent,SubTmp))
						//		{
						//			InSkeletalMeshComponent->SetBodySimulatePhysics(SubTmp, false);
						//		}
						//	}
						//}

						//InSkeletalMeshComponent->WakeAllRigidBodies();
						//InSkeletalMeshComponent->bBlendPhysics = true;
					}
				}
			}
		}
	}
}