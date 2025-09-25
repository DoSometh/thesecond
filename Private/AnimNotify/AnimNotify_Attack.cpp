//Copyright (C) RenZhai.2022.All Rights Reserved.

#include "AnimNotify/AnimNotify_Attack.h"
#include "Hit/ComboSkillHitBox.h"
#include "Hit/ComboSkillHitCapsule.h"
#include "Hit/ComboSkillHitCustom.h"
#include "Hit/ComboSkillHitSphere.h"
#include "GameFramework/Character.h"
#include "CombatInterface/SimpleAttackInterface.h"
#include "SimpleCombatBPLibrary.h"
#include "Components/SkeletalMeshComponent.h"

#if PLATFORM_WINDOWS
#pragma optimize("",off) 
#endif

UAnimNotify_Attack::UAnimNotify_Attack()
	:Super()
{
	HitObjectClass = AHitBoxCollision::StaticClass();
	bEnableClientPrediction = false;
	bHitBox = true;
	bHitCapsule = false;
	bHitCustom = false;
	bHitSphere = false;
	bEnableBuffTag = false;

	BoxExtent = FVector(32.f);
	SphereRadius = 32.f;
	CapsuleHalfHeight = 44.f;
	CapsuleRadius = 22.f;
	LiftTime = 4.f;
	InSocketName = TEXT("OpenFire");

	bUseCurrentCollidingBodySize = true;
	bCustomCaster = false;
//	Direction = FVector::ZeroVector;

	HitSlowTime = 0.001f;
}
#if WITH_EDITORONLY_DATA
FLinearColor UAnimNotify_Attack::GetEditorColor()
{
	return FLinearColor::Red;
}
#endif

#if WITH_EDITOR
void UAnimNotify_Attack::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName().ToString() == TEXT("HitObjectClass"))
	{
		if (!HitObjectClass || !HitObjectClass.GetDefaultObject())
		{
			return;
		}

		if (HitObjectClass.GetDefaultObject()->IsA(AHitBoxCollision::StaticClass()))
		{
			bHitBox = true;
			bHitCapsule = false;
			bHitCustom = false;
			bHitSphere = false;
		}
		else if (HitObjectClass.GetDefaultObject()->IsA(AHitCapsuleCollision::StaticClass()))
		{
			bHitCapsule = true;
			bHitBox = false;
			bHitCustom = false;
			bHitSphere = false;
		}
		else if (HitObjectClass.GetDefaultObject()->IsA(AHitCustiomCollision::StaticClass()))
		{
			bHitCustom = true;
			bHitBox = false;
			bHitCapsule = false;
			bHitSphere = false;
		}
		else if (HitObjectClass.GetDefaultObject()->IsA(AHitSphereCollision::StaticClass()))
		{
			bHitSphere = true;
			bHitBox = false;
			bHitCapsule = false;
			bHitCustom = false;
		}
	}
}
#endif

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

APawn* UAnimNotify_Attack::GetCaster(AActor* InCharacter)
{
	if (bCustomCaster)
	{
		return USimpleCombatBPLibrary::GetCaster(InCharacter);
	}

	return Cast<APawn>(InCharacter);
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	//AAnimationEditorPreviewActor
	if (AActor* InSimpleCombatCharacter = Cast<AActor>(MeshComp->GetOuter()))
	{
		FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
		FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);

		ComponentRotation += RotationOffset;

		FSimpleHitCollisionParam InParam;
		InParam.SimpleCombatCharacter = InSimpleCombatCharacter;
		InParam.HitObjectClass = HitObjectClass.Get();
		InParam.Location = ComponentLocation;
		InParam.Rotation = ComponentRotation;
		InParam.RelativeOffsetLocation = RelativeOffsetLocation;
		InParam.bEnableBuffTag = bEnableBuffTag;
		InParam.Buffs = Buffs;
		InParam.BuffTags = BuffTags;
		InParam.HitID = HitID;
		InParam.HitCollisionLiftTime = LiftTime;
		InParam.bCustomCaster = bCustomCaster;
		InParam.bEnableClientPrediction = bEnableClientPrediction;
		InParam.bUseCurrentCollidingBodySize = bUseCurrentCollidingBodySize;
		InParam.BoxExtent = BoxExtent;
		InParam.CapsuleHalfHeight = CapsuleHalfHeight;
		InParam.BindMesh = MeshComp;
		InParam.bBind = bBind;
		InParam.SocketName = InSocketName;
		InParam.GASTag = GASTag;

		if (AHitCollision* InCollision = USimpleCombatBPLibrary::SpawnCollision(InParam))
		{

		}
	}
}

#if PLATFORM_WINDOWS
#pragma optimize("",on) 
#endif