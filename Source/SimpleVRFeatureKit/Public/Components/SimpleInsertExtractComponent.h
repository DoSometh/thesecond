#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "SimpleVRFeatureKitType.h"
#include "SimpleInsertExtractComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleInsertExtractComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	USimpleInsertExtractComponent();

public:
	//插入的时候执行
	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void Start(const FInsertExtractInfo& InInsertExtractInfo, const FVector& InImpactNormal);

	//彻底拔出执行
	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void End();

public:
	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void Registration(UMotionControllerComponent* InMotionControllerComponent, USceneComponent* InHand);

	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void Deregistration();

public:
	//向量投影
	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	FVector GetInsertExtractRelativePosition() const;

public:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void CheckAttachedComponentParent(USceneComponent* InNewSceneComponent);

protected:
	UPROPERTY()
	FInsertExtractInfo InsertExtractInfo;

	UPROPERTY()
	FVector InitializeRelativePosition;
};