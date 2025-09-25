// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VRTeleportVisualizer.generated.h"

class UNiagaraComponent;

UCLASS()
class SHOOTERVR_API AVRTeleportVisualizer : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = TeleportVisualizer, meta = (AllowPrivateAccess = "true"))
	USceneComponent* VRTeleportVisualizerRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Niagara, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* NSPlayAreaBounds;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Niagara, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* NSTeleportRing;

public:	
	// Sets default values for this actor's properties
	AVRTeleportVisualizer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
