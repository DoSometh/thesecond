#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/BoxComponent.h"
#include "SimpleVRFeatureKitType.h"
#include "SimpleAttachComponent.generated.h"

class IVRFeatureKitInterface;
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_TwoParams(FAttachDynamicMulticast, USimpleAttachComponent, AttachDynamicDelegate, USimpleAttachComponent*,InSimpleAttachComponent, EAttachInfoType, InAttachInfoType);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleAttachComponent : public UBoxComponent
{
	GENERATED_BODY()

	//可以附加的ID类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float AttachSpeed;

	//附加的一个比较值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float AttachTolerance;

public:
	UPROPERTY(BlueprintAssignable, Category = Attach)
	FAttachDynamicMulticast AttachDynamicDelegate;

public:
	USimpleAttachComponent();

	UFUNCTION(BlueprintPure, Category = "Attach")
	int32 GetID() const { return ID; }

	UFUNCTION(BlueprintPure, Category = "Attach")
	AActor* GetCurrentAttachVRKitInterface() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	virtual void OnAttachBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAttachEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TWeakObjectPtr<AActor> TmpAttachObject;
	TWeakObjectPtr<AActor> LastTmpAttachObject;
};