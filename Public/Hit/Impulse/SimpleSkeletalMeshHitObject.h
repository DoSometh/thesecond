#pragma once

#include "CoreMinimal.h"
#include "Timer/SimpleTimerManage.h"
#include "SimpleSkeletalMeshHitObject.generated.h"

class USkeletalMeshComponent;
enum class EItemObjectState : uint8;

USTRUCT(BlueprintType)
struct SIMPLECOMBAT_API FSimpleSkeletalMeshHitObject
{
	GENERATED_USTRUCT_BODY()

	TWeakObjectPtr<USkeletalMeshComponent> MeshComponent;

	//队列状态
	UPROPERTY()
	EItemObjectState State;

	UPROPERTY()
	FName BoneName;

	UPROPERTY()
	TArray<FName> ExcludeBoneName;

	UPROPERTY()
	FVector ImpactNormal;

	UPROPERTY()
	float Impulse;

	//子项的深度
	UPROPERTY()
	int32 SubTargetDepth;

	//缓存
	UPROPERTY()
	bool bCacheBuildBones;

	//是否本地冲量 如果它为ture代表只有本身骨骼受到冲量
	UPROPERTY()
	bool bLocalImpulse;

public:
	FSimpleSkeletalMeshHitObject();

	void Tick(float DeltaTime);

	void Init(
		USkeletalMeshComponent* InMeshComponent,
		int32 InSubTargetDepth,
		bool bNewLocalImpulse,
		float InTime,
		const FName& InBoneName,
		float InImpulse,
		const FVector& InImpactNormal,
		const TArray<FName>& InExcludeBoneName);

	bool IsFree() const;

protected:
	void Start();
	void OnGoing(float InRatio, float DeltaTime);
	void End();

	void SetPhysicalSimulation(FName InBoneName,bool bNewPhysical);

protected:
	//获取直接子节点骨骼（手动遍历实现）
	TArray<FName> GetDirectChildrenBones(USkeletalMeshComponent* SkeletalMeshComponent, FName ParentBoneName);
	// 获取特定深度的子节点（改进版 BFS）
	TArray<FName> GetBonesAtDepth(USkeletalMeshComponent* SkeletalMeshComponent, FName RootBoneName, int32 TargetDepth);
	
	// 在初始化时构建 <父索引 -> 子索引列表> 的映射 [针对优化]
	void BuildBoneHierarchyCache(USkeletalMeshComponent* SkeletalMeshComponent);

protected:
	FSimpleTimerManage Timer;
	TMap<int32, TArray<int32>> BoneHierarchyCache;
};