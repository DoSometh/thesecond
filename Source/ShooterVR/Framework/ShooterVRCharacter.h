// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/FrameworkCharacterBase.h"
#include "ShooterVRCharacter.generated.h"

class UCameraComponent;
class UMotionControllerComponent;
class USceneComponent;
class UNiagaraComponent;
class AVRTeleportVisualizer;
class AShooterVRHand;
class UGameplayAbility;

enum class EVRHandType :uint8;

UCLASS()
class SHOOTERVR_API AShooterVRCharacter : public AFrameworkCharacterBase
{
	GENERATED_BODY()

	//����ͷ�Ͳ��ӵķ�Χ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	//����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VRController, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* ControllerRight;

	//����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VRController, meta = (AllowPrivateAccess = "true"))
	UMotionControllerComponent* ControllerLeft;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = VRController, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> VRSystem;

	/// <summary>
	/// ����
	/// </summary>
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Niagara, meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* TeleportTraceNiagaraSystem;

	//��Ҫ�ڱ༭�������������
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Niagara, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AVRTeleportVisualizer> VRTeleportVisualizerClass;

	//�ֵ�����
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Hand, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AShooterVRHand> VRShooterHandClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value , meta = (AllowPrivateAccess = "true"))
	float SnapTurnDegrees;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Value, meta = (AllowPrivateAccess = "true"))
	float LocalTeleportLaunchSpeed;

public:
	// Sets default values for this character's properties
	AShooterVRCharacter();

public:
	void SpawnHand(EVRHandType InType);

public:
	void SnapTurn(bool bRight);

	/////////////////////////////////////////
	//�������� ������
	void StartTeleportTrace();
	void TeleportTrace();
	void EndTeleportTrace();

	//����
	void TryTeleport();
	/////////////////////////////////////////

	void MoveForward(float Value);
	void MoveRight(float Value);

	/////////////////////////////////////////
	void GrabLeftPressed();
	void GrabLeftReleased();

	void GrabRightPressed();
	void GrabRightReleased();

	void LeftDrag();
	void LeftDragEnd();

	void RightDrag();
	void RightDragEnd();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	FORCEINLINE UNiagaraComponent* GetTeleportTraceNiagaraSystem() const { return TeleportTraceNiagaraSystem; }

public:

	void SetUserCurvePointArray(const TArray<FVector>& InPointArray);
	void SetTeleportTraceNiagaraVisibility(bool bVisibility);
	
protected:
	//�����ƶ�λ��
	UPROPERTY()
	bool bTeleportTraceActive;

	//�ǲ�����Ч�ĵ�������
	UPROPERTY()
	bool bValidTeleportLocation;

	//�����ߺ͵���Ľ���
	UPROPERTY()
	FVector ProjectedLocation;

	UPROPERTY()
	AVRTeleportVisualizer* VRTeleportVisualizer;

	UPROPERTY()
	AShooterVRHand* RightHand;

	UPROPERTY()
	AShooterVRHand* LeftHand;
};
