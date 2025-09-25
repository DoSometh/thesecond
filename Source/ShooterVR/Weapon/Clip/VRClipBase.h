// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleModularActor.h"
#include "VRClipBase.generated.h"

class USimpleGrabComponent;
class UStaticMeshComponent;
class ASimulationModel;

UCLASS()
class SHOOTERVR_API AVRClipBase : public ASimpleModularActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Clip, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USimpleGrabComponent> GrabComponent;

	UPROPERTY(Category = Weapon, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> ClipMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	int32 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASimulationModel> BulletModelClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASimulationModel> UsedBulletModelClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Bullet, meta = (AllowPrivateAccess = "true"))
	int32 BulletNumber;

	//∞≤◊∞«π…˘“Ù
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Install Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr <USoundBase> InstallSoundCue;

	//…˘“Ù…Ë÷√
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Install Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundAttenuation> SoundAttenuation;
public:
	AVRClipBase();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure, Category = "Weapon|ID")
	FORCEINLINE int32 GetID() const { return ID; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Components|Grab")
	bool TryRelease();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Bullet")
	ASimulationModel* SpawnBulletModel(const FVector& InLocation, const FRotator& InRotation);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Bullet")
	ASimulationModel* SpawnUsedBulletModel(const FVector& InLocation, const FRotator& InRotation);

	UFUNCTION(BlueprintCallable, Category = "Weapon|Bullet")
	void StartSelfDestruction();

	UFUNCTION(BlueprintCallable, Category = "Weapon|Bullet")
	void PlayInstallSound();
public:
	bool IsEnoughBullets()const { return BulletNumber > 0; }
	int32 GetBulletNumer() const { return BulletNumber; }
	void SetBulletNumber(float InNewBulletNumer) { BulletNumber = InNewBulletNumer; }
protected:
	ASimulationModel* SpawnSimulationModel(TSubclassOf<ASimulationModel> InCalss,const FVector& InLocation, const FRotator& InRotation);

public:
	AActor* GetAttachObject() const;
	USimpleGrabComponent* GetGrabComponent() const { return GrabComponent; }
};