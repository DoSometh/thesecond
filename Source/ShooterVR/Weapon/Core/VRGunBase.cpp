// Fill out your copyright notice in the Description page of Project Settings.
#include "VRGunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SimpleGrabComponent.h"
#include "Components/SimpleSliderComponent.h"
#include "Components/SimpleClipComponent.h"
#include "Components/ArrowComponent.h"
#include "../../Framework/ShooterVRPlayerController.h"
#include "../../Framework/ShooterVRHand.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "../Clip/VRClipBase.h"
#include "../../AbilitiesSystem/AttributeSet/VRGunAttributeSet.h"
#include "Kismet/GameplayStatics.h"

AVRGunBase::AVRGunBase()
{
	LeftHandle = NULL;
	RightHandle = NULL;

	SliderTrigger = CreateDefaultSubobject<USimpleSliderComponent>(TEXT("SliderTrigger"));
	SliderTrigger->SetupAttachment(RootComponent);

	ClipComponent = CreateDefaultSubobject<USimpleClipComponent>(TEXT("ClipComponent"));
	ClipComponent->SetupAttachment(RootComponent);

	BullectSpawnArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BullectSpawnArrow"));
	BullectSpawnArrow->SetupAttachment(RootComponent);

	SlingClipDistanceByFrame = 7.f;

	bLoading = false;

	bUpperSpringClip = false;
}

void AVRGunBase::BeginPlay()
{
	Super::BeginPlay();

	OpenFireHandle = RegisterGameplayAbility(GameplayAbility_OpenFire);

	SliderTrigger->OnComponentBeginOverlap.AddDynamic(this, &AVRGunBase::OnSliderBeginOverlap);
	SliderTrigger->OnComponentEndOverlap.AddDynamic(this, &AVRGunBase::OnSliderEndOverlap);

	ClipComponent->OnComponentBeginOverlap.AddDynamic(this, &AVRGunBase::OnClipBeginOverlap);
	ClipComponent->OnComponentEndOverlap.AddDynamic(this, &AVRGunBase::OnClipEndOverlap);

	SliderTrigger->StartPullupDelegate.AddDynamic(this, &AVRGunBase::OnStartPullup);
	SliderTrigger->EndPullupDelegate.AddDynamic(this, &AVRGunBase::OnEndPullup);
	SliderTrigger->StartSpringbackDelegate.AddDynamic(this, &AVRGunBase::OnStartSpringback);
	SliderTrigger->EndSpringbackDelegate.AddDynamic(this, &AVRGunBase::OnEndSpringback);
	SliderTrigger->SlidingDelegate.AddDynamic(this, &AVRGunBase::OnSliding);
	AttributeSet = const_cast<UVRGunAttributeSet*>(GetAbilitySystemComponent()->AddSet<UVRGunAttributeSet>());

	RegistrationAttribute();
}

void AVRGunBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnregisterGameplayAbility(OpenFireHandle);
}

void AVRGunBase::OnSlingClip()
{
	if (AVRClipBase* InClipBase = GetClipActor())
	{
		if (!InClipBase->IsEnoughBullets())
		{
			InClipBase->TryRelease();

		
			InClipBase->StartSelfDestruction();
		}
		else 
		{
			SetBulletNumber(InClipBase,true,false);
		}
	}
}

bool AVRGunBase::IsFullBullets() const
{
	return AttributeSet->GetBulletsNumber() == AttributeSet->GetMaxBulletsNumber();
}

EVRHandType AVRGunBase::GetHandType() const
{
	if (GetGrabComponent())
	{
		if (const AShooterVRHand* InVRHand = Cast<AShooterVRHand>(GetGrabComponent()->GetAttachObject()))
		{
			return InVRHand->GetHandType();
		}
	}

	return EVRHandType::VR_MAX;
}

void AVRGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsHeld())
	{
		if (AActor* InParentActor = GetAttachParentActor())
		{
			FVector CurrentRelativePosition = GetRelativeAttachParentActorPosition();
			float CurrentDistance = FVector::Distance(CurrentRelativePosition,LastRelativeAttachParentActorPosition);
		
			if (CurrentDistance > SlingClipDistanceByFrame)
			{
				if (!IsEnoughBullets())
				{
					OnSlingClip();
				}	
			}

			LastRelativeAttachParentActorPosition = CurrentRelativePosition;
		}
	}
}

void AVRGunBase::Release()
{
	if (AShooterVRPlayerController* InPlayerController = GetWorld()->GetFirstPlayerController<AShooterVRPlayerController>())
	{
		InPlayerController->RemoveInputMappingContext(GetInputMappingContext());

		RemoveAction();
	}
}

void AVRGunBase::BindAction()
{
	if (UEnhancedInputComponent* InEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent))
	{
		switch (GetHandType())
		{
			case EVRHandType::VR_RIGHT:
			{
				if (IATriggerRight)
				{
					RightHandle = &InEnhancedInputComponent->BindAction(IATriggerRight, ETriggerEvent::Triggered, this, &AVRGunBase::TriggerRight);
				}
				break;
			}
			case EVRHandType::VR_LEFT:
			{
				if (IATriggerLeft)
				{
					LeftHandle = &InEnhancedInputComponent->BindAction(IATriggerLeft, ETriggerEvent::Triggered, this, &AVRGunBase::TriggerLeft);
				}
				break;
			}
		}
	}
}
void AVRGunBase::RemoveAction()
{
	if (UEnhancedInputComponent* InEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(GetWorld()->GetFirstPlayerController()->InputComponent))
	{
		switch (GetHandType())
		{
			case EVRHandType::VR_RIGHT:
			{
				if (RightHandle)
				{
					InEnhancedInputComponent->RemoveBinding(*RightHandle);
				}

				break;
			}
			case EVRHandType::VR_LEFT:
			{
				if (LeftHandle)
				{
					InEnhancedInputComponent->RemoveBinding(*LeftHandle);
				}

				break;
			}
		}
	}
}

void AVRGunBase::Grab()
{
	if (AShooterVRPlayerController *InPlayerController = GetWorld()->GetFirstPlayerController<AShooterVRPlayerController>())
	{
		InPlayerController->AddInputMappingContext(GetInputMappingContext(),0);

		BindAction();
	}

	LastRelativeAttachParentActorPosition = GetRelativeAttachParentActorPosition();
}

void AVRGunBase::TriggerLeft(const FInputActionValue& InInputValue)
{
	OpenFire(InInputValue);
}

void AVRGunBase::TriggerRight(const FInputActionValue& InInputValue)
{
	OpenFire(InInputValue);
}

void AVRGunBase::OpenFire(const FInputActionValue& InInputValue)
{
	if (AVRClipBase* InClip = GetClipActor())
	{
		if (IsEnoughBullets())
		{
			if (bLoading)
			{
				//
				ExecuteGameplayAbility(OpenFireHandle);
				//
				ExecuteGameplayEffect(BulletConsumeClass);
				//
				InClip->SpawnUsedBulletModel(
					BullectSpawnArrow->GetComponentLocation(),
					BullectSpawnArrow->GetComponentRotation());
				CheckNeedLoading();
			}
			else
			{
				PlayEmptyOpenFireMontage();
			}
		}
		else
		{
			PlayEmptyOpenFireMontage();
		}
	}
	else
	{
		PlayEmptyOpenFireMontage();
	}
}

void AVRGunBase::HandlingBullets(
	AVRClipBase* InClipBase, 
	float InCurrentBulletNumber,
	float InNumberBulletsLeft, 
	bool bInstallClip)
{
	if (bInstallClip)
	{
		InClipBase->TryRelease();

		InClipBase->SetBulletNumber(InNumberBulletsLeft);
	}
	else
	{
		if (InNumberBulletsLeft <= 0)
		{
			//
			InClipBase->TryRelease();

			//
			InClipBase->Destroy();
		}
		else
		{
			InClipBase->SetBulletNumber(InNumberBulletsLeft);
		}
	}
}

void AVRGunBase::SetBulletNumber(AVRClipBase* InClipBase, bool bInstallClip, bool bHandlingBullets)
{
	//
	bUpperSpringClip = false;

	float TotalBulletNumer = (float)InClipBase->GetBulletNumer() + AttributeSet->GetBulletsNumber();

	AttributeSet->SetBulletsNumber((float)InClipBase->GetBulletNumer());
	float SurplusBulletNumber = FMath::Max(0.f,TotalBulletNumer - AttributeSet->GetMaxBulletsNumber());
	//
	AttributeSet->SetBulletsNumber(
		FMath::Clamp(AttributeSet->GetBulletsNumber(), 0.f, AttributeSet->GetMaxBulletsNumber()));

	if (bHandlingBullets)
	{
		HandlingBullets(InClipBase, AttributeSet->GetBulletsNumber(), SurplusBulletNumber, bInstallClip);
	}
}

void AVRGunBase::CheckNeedLoading()
{
	if (!IsEnoughBullets())
	{
		bLoading = false;

		//֪ͨ������ͼ �ӵ�û�� �ص���
		bUpperSpringClip = true;

		//ֹͣ���ж���
		StopAnimMontage();
	}
}

bool AVRGunBase::IsEnoughBullets() const
{
	return AttributeSet->GetBulletsNumber() > 0.f;
}

UInputMappingContext* AVRGunBase::GetInputMappingContext()const
{
	switch (GetHandType())
	{
		case EVRHandType::VR_RIGHT:
		{
			return IMCGunRightGamepadContext;
		}
		case EVRHandType::VR_LEFT:
		{
			return IMCGunLeftGamepadContext;
		}
	}

	return NULL;
}

UVRAttributeSetBase* AVRGunBase::GetAttribute() const
{
	return AttributeSet;
}

FVector AVRGunBase::GetIncrementPosition() const
{
	return SliderTrigger->GetIncrementPosition();
}

AVRClipBase* AVRGunBase::GetClipActor() const
{
	auto ClipAttachChildren = ClipComponent->GetAttachChildren();
	if (ClipAttachChildren.Num() > 0)
	{
		return Cast<AVRClipBase>(ClipAttachChildren[0]->GetOwner());
	}

	return nullptr;
}

FVector AVRGunBase::GetRelativeAttachParentActorPosition() const
{
	if (const AActor* InParentActor = GetAttachParentActor())
	{
		return InParentActor->GetActorTransform().InverseTransformPosition(GetActorLocation());
	}

	return FVector();
}

void AVRGunBase::OnSliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AShooterVRHand::StaticClass()))
	{
		if (AShooterVRHand* InHandA = Cast<AShooterVRHand>(GetAttachObject()))
		{
			if (InHandA != OtherActor)
			{
				if (AShooterVRHand* InHandB = Cast<AShooterVRHand>(OtherActor))
				{
					InHandB->SetEnableSliderTrace(true);
				}
			}
		}
	}
}

void AVRGunBase::OnSliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(AShooterVRHand::StaticClass()))
	{
		if (AShooterVRHand* InHandA = Cast<AShooterVRHand>(GetAttachObject()))
		{
			if (InHandA != OtherActor)
			{
				if (AShooterVRHand* InHandB = Cast<AShooterVRHand>(OtherActor))
				{
					InHandB->SetEnableSliderTrace(false);
				}
			}
		}
	}
}

//装填子弹
void AVRGunBase::OnClipBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AVRClipBase* InBClipBase = Cast<AVRClipBase>(OtherActor))
	{
		if (InBClipBase->GetID() == GetID())//
		{
			if (InBClipBase->IsEnoughBullets())
			{
				if (AVRClipBase* InAClipBase = GetClipActor())
				{
					if (InBClipBase != InAClipBase)
					{
						if (!IsFullBullets())//
						{
							InBClipBase->PlayInstallSound();

							//
							SetBulletNumber(InBClipBase, false);
						}
						else
						{

						}
					}
				}
				else
				{
					//
					SetBulletNumber(InBClipBase, true);

					//
					FAttachmentTransformRules AttachmentTransformRules(
						EAttachmentRule::SnapToTarget,
						EAttachmentRule::SnapToTarget,
						EAttachmentRule::KeepWorld,
						true);

					InBClipBase->GetRootComponent()->AttachToComponent(
						ClipComponent,
						AttachmentTransformRules);

					InBClipBase->PlayInstallSound();
				}
			}
		}
	}
}

void AVRGunBase::OnClipEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AVRGunBase::OnSliding(float InRatio, bool bRebound)
{
	//
	GetGrabComponent()->PlayHapticEffect(
		SliderbackFeedbackEffect,
		FMath::Clamp((bRebound == false ? 1.f - InRatio : InRatio), 0.f, 1.f));
}

void AVRGunBase::OnEndSpringback()
{
	if (!bUpperSpringClip)
	{

	}
}

void AVRGunBase::OnStartSpringback()
{
	if (!bUpperSpringClip)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			SliderSpringbackSoundCue,
			GetActorLocation(),
			FRotator::ZeroRotator,
			1, 1,
			SliderSpringbackSoundStartTime,
			SoundAttenuation);
	}
}

void AVRGunBase::OnEndPullup()
{
	if (!bUpperSpringClip)
	{
		if (AVRClipBase* InClip = GetClipActor())
		{
			if (IsEnoughBullets())
			{
				if (bLoading)
				{
					//�۵�buff
					ExecuteGameplayEffect(BulletConsumeClass);

					InClip->SpawnBulletModel(
						BullectSpawnArrow->GetComponentLocation(),
						BullectSpawnArrow->GetComponentRotation());

					CheckNeedLoading();
				}
				else
				{
					bLoading = true;
				}
			}
		}
	}
}

void AVRGunBase::OnStartPullup()
{
	if (!bUpperSpringClip)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			SliderPullSoundCue,
			GetActorLocation(),
			FRotator::ZeroRotator,
			1, 1,
			SliderPullSoundStartTime,
			SoundAttenuation);
	}
}

void AVRGunBase::PlayEmptyOpenFireMontage()
{
	if (EmptyOpenFireMontage)
	{
		PlayAnimMontage(EmptyOpenFireMontage);
	}
}