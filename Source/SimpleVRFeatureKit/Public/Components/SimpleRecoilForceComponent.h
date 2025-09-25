#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/ActorComponent.h"
#include "SimpleRecoilForceComponent.generated.h"

class USceneComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleRecoilForceComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = RecoilForce, meta = (AllowPrivateAccess = "true"))
	bool bEnableRecoilForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = RecoilForce, meta = (EditCondition = "bEnableRecoilForce", AllowPrivateAccess = "true"))
	FRotator RecoilForceOffset;

public:
	USimpleRecoilForceComponent();

public:
	UFUNCTION(BlueprintCallable, Category = "Components|RecoilForce")
	virtual void PlayRecoilForce();

	UFUNCTION(BlueprintCallable, Category = "Components|RecoilForce")
	virtual void RegisterRecoilForce();

	UFUNCTION(BlueprintCallable, Category = "Components|RecoilForce")
	virtual void UnregisteredRecoilForce();

protected:
	void ResetAttachRootComponentRotator();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	TWeakObjectPtr<USceneComponent> AttachRootComponent;

	UPROPERTY()
	FRotator IncrementRotator;

	UPROPERTY()
	bool bRecoilForce;
};
