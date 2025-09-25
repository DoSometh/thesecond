//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "ComboHitBase.h"
#include "ComboSkillHitCollision.generated.h"

class USplineComponent;
class USceneComponent;
class UProjectileMovementComponent;
class URotatingMovementComponent;

DECLARE_DELEGATE_SixParams(FHandleDamageStart, UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32, bool, const FHitResult&);
DECLARE_DELEGATE_FourParams(FHandleDamageEnd, UPrimitiveComponent*, AActor*, UPrimitiveComponent*, int32);

//用于碰撞后的检测
UENUM(BlueprintType)
enum class EVRCollisionCheckType :uint8
{
	//点，更适合射击
	CC_LINE						UMETA(DisplayName = "Line"),
	//box作为射线 一般用于近战 刀剑
	CC_BOX						UMETA(DisplayName = "Box"),
};

//碰撞后应该如何销毁
UENUM(BlueprintType)
enum class EVRCollisionDestroyType :uint8
{
	//立即销毁
	CD_IMMEDIATELY_DESTROY						UMETA(DisplayName = "Immediately"),
	//自定义销毁
	CD_DELAY_DESTRUCTION						UMETA(DisplayName = "Delay"),
	//自己决定如何销毁
	CD_DELAY_Customize							UMETA(DisplayName = "Customize"),
};

//主要作用为了记录被录入的敌人时间，平均一秒阻碍
USTRUCT(BlueprintType)
struct FAttackedTargetTimer
{
	GENERATED_USTRUCT_BODY()

	FAttackedTargetTimer();

	FAttackedTargetTimer(ACharacter* InNewCharacter);

	UPROPERTY()
	TWeakObjectPtr<ACharacter> AttackedTarget;

	UPROPERTY()
	float Time;
};

inline bool operator==(const FAttackedTargetTimer& Left, const FAttackedTargetTimer& Right)
{
	return Left.AttackedTarget == Right.AttackedTarget;
}

UCLASS(BlueprintType, Blueprintable)
class SIMPLECOMBAT_API AHitCollision : public AComboHitBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HitCollision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URotatingMovementComponent> RotatingMovementComponent;

public:
	FHandleDamageStart OnPreHandleDamageStart;
	FHandleDamageStart OnPostHandleDamageStart;
	FHandleDamageEnd OnHandleDamageEnd;

public:
	//类型 是希望它是直线攻击还是受击还是 跟踪 还是范围爆炸等
	UPROPERTY(EditDefaultsOnly, Category = "HitCollision")
	EHitCollisionType HitCollisionType;

	//当开启 bEnableSweep 的时候 可以选择对应 类型
	UPROPERTY(EditDefaultsOnly, Category = "HitCollision")
	EVRCollisionCheckType CollisionCheckType;

	//开火点 方便绑定
	UPROPERTY(EditDefaultsOnly, Category = "HitCollision")
	FName OpenFirePoint;

	//随机范围
	UPROPERTY(EditDefaultsOnly, Category = "HitCollision")
	bool bRandomDirection;

	//该变量需要 HitCollisionType == EHitCollisionType::HITCOLLISIONTYPE_RAY_LINE 才有效果,射线的检测距离
	UPROPERTY(EditDefaultsOnly, Category = "Line Trace HitCollision")
	float TraceDistance;

	//射线统一检测通道
	UPROPERTY(EditDefaultsOnly, Category = "HitCollision")
	TEnumAsByte<ETraceTypeQuery> TraceTypeQuery;

	//该值只为范围爆炸攻击提供
	UPROPERTY(EditDefaultsOnly, Category = "Range HitCollision")
	float BaseDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Range HitCollision")
	float MinimumDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Range HitCollision")
	float DamageInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Range HitCollision")
	float DamageOuterRadius;

	//针对	HITCOLLISIONTYPE_DIRECT_LINE ，	无障碍直线攻击 有弹道
	//		HITCOLLISIONTYPE_LINE，			非跟踪类型，类似手枪子弹 有弹道；
	//		HITCOLLISIONTYPE_TRACK_LINE		跟踪类型 有弹道
	//类型开启碰撞射线检测 对有弹道的非常有效果
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	bool bEnableSweep;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	ESimpleDrawDebugTrace DrawDebugTrace;

	//是不是只记录一次 接受到的敌人，如果为false 每次攻击接受到敌人后 一秒后可再接受此敌人
	//如果为true, 赋予伤害过的敌人将不再赋予伤害
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	bool bRecordOnlyOnce;

	//是否开启Debug效果
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Debug")
	bool bDebugHitLine;

	//完成任务后应该如何销毁
	UPROPERTY(EditDefaultsOnly, Category = "Line Trace HitCollision")
	EVRCollisionDestroyType CollisionDestroyType;

	//当进行延迟销毁 将执行本接口
	UPROPERTY(EditDefaultsOnly, Category = "Line Trace HitCollision")
	float DelayDestroy;

public:
	AHitCollision(const FObjectInitializer& ObjectInitializer);

	virtual void PreInitCollision(AActor* InMyInstigator);

	virtual void HandleDamage(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ActivateProjectileMovement(float InMaxSpeed, const FVector& InVelocity, bool bActivateGravity, bool bRot = false);
	void ActivateProjectileMovementHoming(AActor* InTarget, float HomingAccelerationMagnitude, bool bRot = false);

	void StopTrack(AActor* InTrackTarget);
	void ReleaseGAS();

public:
	void ShowHitResultDebug(const FHitResult& SweepResult);

public:
	void SetBuffs(const TArray<FName>& InBuffs) { Buffs = InBuffs; }
	void SetBuffs(const TArray<FGameplayTag>& InBuffs) { BuffTags = InBuffs; }

public:
	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void SetHitDamageRelativePosition(const FVector& InNewPostion);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void SetHitID(int32 InNewHit) { HitID = InNewHit; }

	UFUNCTION(BlueprintCallable, Category = "HitCollision", meta = (DisplayName = "SetBuffs(Name)"))
	void K2_SetBuffsByName(const TArray<FName>& InBuffs);

	UFUNCTION(BlueprintCallable, Category = "HitCollision", meta = (DisplayName = "SetBuffs(GameplayTag)"))
	void K2_SetBuffsByTag(const TArray<FGameplayTag>& InBuffs);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void SetIgnoreActors(const TArray<AActor*> &InActors);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void SetIgnoreActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void Collision(bool bCollision);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void InitCustomIgnoreActors();

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void ClearCustomIgnoreActors();

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void AddIgnoreActors(AActor* InNewActor);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void RemoveIgnoreActors(AActor* InNewActor);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void SetScapegoatActor(AActor* InScapegoat) { ScapegoatActor = InScapegoat; }

	//该接口由上层用户调用 决定是否销毁该对象
	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void CheckAutomaticallyDestroy();

	//受到攻击
	UFUNCTION(BlueprintImplementableEvent, Category = "Gun|Event", meta = (DisplayName = "EventAffected"))
	void K2_OnAffected();

	UFUNCTION(BlueprintImplementableEvent, Category = "Gun|Event", meta = (DisplayName = "ActivateProjectileMovementHoming"))
	void K2_OnActivateProjectileMovementHoming();

	//快速完成注册和卸载（需要手动完成）
	//提供非 AnimNotif 和非库生成的内容
public:
	//非动画AnimNotif生成 或者 是非USimpleCombatBPLibrary::SpawnSimpleCollision 生成
	//需要调用该接口来初始化
	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	virtual void InitHitCollision(AActor* InParentActor = NULL);

	//用于初始化绑定事件
	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	virtual void InitHitBindEvent(AActor* InParentActor = NULL);

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	virtual void UnregisteredHitCollision();

	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	virtual void RegisterHitCollision(AActor* InActor);

	//设置当前的GAS标签
	UFUNCTION(BlueprintCallable, Category = "HitCollision")
	void SetGASTag(const FGameplayTag& InTag) { GASTag = InTag; }

public:
	UFUNCTION(BlueprintPure, Category = "HitCollision")
	virtual UPrimitiveComponent* GetHitDamage();

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	AActor* GetScapegoatActor() const { return ScapegoatActor; }

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	bool IsExitIgnoredActor(AActor* InActor) const;

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	const int32 GetHitID() const { return HitID; }

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	bool IsExist(ACharacter *InNewTaget)const;

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	const TArray<FGameplayTag> &GetBuffTags() const { return BuffTags; }

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	const TArray<FName>& GeBuffs() const { return Buffs; }

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	const TArray<FAttackedTargetTimer>& GetAttackedTarget() const { return AttackedTarget; }

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	float GetDamageRatio() const { return DamageRatio; }

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	void GetIgnoreTraceActor(TArray<AActor*> &OutActorsToIgnore);

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	virtual FVector GetExtent() const { return FVector::ZeroVector; };

	UFUNCTION(BlueprintPure, Category = "HitCollision")
	bool IsLocallyInputControlled() const;

protected:
	UFUNCTION()
	virtual void StartHandleDamage_Inner(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void EndHandleDamage_Inner(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	virtual void RadialDamage();

protected:
	//针对方向直线的本地缓存
	UPROPERTY()
	FHitResult DirectionalLineHitResult;

	UPROPERTY()
	FTransform InitTransform;

	UPROPERTY()
	USplineComponent* Spline;

	UPROPERTY()
	float SplineOffset;

	UPROPERTY()
	int32 HitID;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TArray<FName> Buffs;

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	TArray<FGameplayTag> BuffTags;

	UPROPERTY()
	TArray<FAttackedTargetTimer> AttackedTarget;

	UPROPERTY()
	TArray<TWeakObjectPtr<AActor>> CustomIgnoreActors;

	UPROPERTY()
	AActor* ScapegoatActor;

	UPROPERTY()
	float CurrentSplineTime;

	UPROPERTY()
	FVector DistanceVector;

	UPROPERTY()
	float DamageRatio;

	UPROPERTY()
	bool bPreInitCollision;

	UPROPERTY()
	bool bTrack;

	UPROPERTY()
	FGameplayTag GASTag;

private:
	FVector LastPos;
	TArray<float> MoveLengths;

public:
	float GetMoveSpeed(int32 NumFrame);

};