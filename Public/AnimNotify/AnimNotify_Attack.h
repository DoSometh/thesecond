//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_Attack.generated.h"

class AHitCollision;
class APawn;

UCLASS(meta = (DisplayName = "Attack"))
class SIMPLECOMBAT_API UAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_Attack();

#if WITH_EDITORONLY_DATA
	virtual FLinearColor GetEditorColor();
#endif

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,const FAnimNotifyEventReference& EventReference) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif

	APawn* GetCaster(AActor* InCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	TSubclassOf<AHitCollision> HitObjectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	int32 HitID;
	
	//当受击后会有慢速效果(网络暂时不支持)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	float HitSlowTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	bool bEnableBuffTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration", meta = (EditCondition = "!bEnableBuffTag"))
	TArray<FName> Buffs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration", meta = (EditCondition = "bEnableBuffTag"))
	TArray<FGameplayTag> BuffTags;

	//GAS标签 方便技能box释放
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FGameplayTag GASTag;

	//如果为false 代表只能服务器生成 如果为true 服务器客户端都可以生成 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	bool bEnableClientPrediction;

	//碰撞体的相对位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FVector RelativeOffsetLocation;
	
	//碰撞体的相对位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FRotator RotationOffset;
	
	//存在的生命周期
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	float LiftTime;

	////方向
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	//FVector Direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	FName InSocketName;

	//将Box绑定在角色身上开火点上
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	bool bBind;

	//自定义施法者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	bool bCustomCaster;

	//群体攻击还是单体攻击
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General configuration")
	bool bSingleTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Box")
	bool bUseCurrentCollidingBodySize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Box", meta = (EditCondition = "bHitBox"))
	FVector BoxExtent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Sphere", meta = (EditCondition = "bHitSphere"))
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Capsule", meta = (EditCondition = "bHitCapsule"))
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hit Capsule", meta = (EditCondition = "bHitCapsule"))
	float CapsuleRadius;

public:
	UPROPERTY(BlueprintReadOnly, Category = "Hit")
	bool bHitBox;

	UPROPERTY(BlueprintReadOnly, Category = "Hit")
	bool bHitSphere;

	UPROPERTY(BlueprintReadOnly, Category = "Hit")
	bool bHitCustom;

	UPROPERTY(BlueprintReadOnly, Category = "Hit")
	bool bHitCapsule;
};
