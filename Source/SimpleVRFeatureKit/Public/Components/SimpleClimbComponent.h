#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/ActorComponent.h"
#include "SimpleVRFeatureKitType.h"
#include "SimpleClimbComponent.generated.h"

class UMotionControllerComponent;
class USimpleVRMovementComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleClimbComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USimpleClimbComponent();

public:
	bool TryGetVRMovement();

	int32 StartClimb(AActor* InHand, UMotionControllerComponent* InMotionController, UPrimitiveComponent* InClimbObject);
	void EndClimb(int32 InHandle);

	void UpdateClimb(float DeltaTime);

public:
	int32 SpawnNonrepeatableHandle() const;
	bool Contains(int32 InHandle) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TArray<FVRClimbInfo> ClimbInfo;

	UPROPERTY()
	TWeakObjectPtr<USimpleVRMovementComponent> VRMovementComponent;
};