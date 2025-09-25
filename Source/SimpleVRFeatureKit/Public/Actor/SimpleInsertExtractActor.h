//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleInsertExtractActor.generated.h"

class USimpleInsertExtractComponent;

UCLASS()
class SIMPLEVRFEATUREKIT_API ASimpleInsertExtractActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = InsertExtract, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USimpleInsertExtractComponent> InsertExtractComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = InsertExtract, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> InsertExtractRootComponent;

public:
	ASimpleInsertExtractActor();

public:
	virtual void PreInit();
	virtual void PostInit();

public:
	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void Start(const FInsertExtractInfo& InInsertExtractInfo, const FVector& InImpactNormal);

	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void End();

	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void Registration(UMotionControllerComponent* InMotionControllerComponent, USceneComponent* InHand);

	UFUNCTION(BlueprintCallable, Category = "InsertExtract|Attach")
	virtual void Deregistration();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};