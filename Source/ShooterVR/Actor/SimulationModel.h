// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimulationModel.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;


UCLASS()
class SHOOTERVR_API ASimulationModel : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TeleportVisualizer, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> SimulationModelRoot;
	
	UPROPERTY(Category = Mesh, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	//¬‰µÿµƒ…˘“Ù
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> CollisionSoundCue;

	//…˘“Ù…Ë÷√
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundAttenuation> SoundAttenuation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;
public:	
	// Sets default values for this actor's properties
	ASimulationModel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
