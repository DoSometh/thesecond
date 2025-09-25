// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterVRPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ShooterVRCharacter.h"

void AShooterVRPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* InEnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		if (IATriggerLeft)
		{
			InEnhancedInputComponent->BindAction(IATriggerLeft, ETriggerEvent::Triggered,this,&AShooterVRPlayerController::TriggerLeft);
		}

		if (IATriggerLeftTrackpakL)
		{
			InEnhancedInputComponent->BindAction(IATriggerLeftTrackpakL, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerLeftTrackpakL);
		}

		if (IATriggerLeftTrackpakR)
		{
			InEnhancedInputComponent->BindAction(IATriggerLeftTrackpakR, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerLeftTrackpakR);
		}

		if (IATriggerRight)
		{
			InEnhancedInputComponent->BindAction(IATriggerRight, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerRight);
		}

		if (IATriggerRightTrackpakL)
		{
			InEnhancedInputComponent->BindAction(IATriggerRightTrackpakL, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerRightTrackpakL);
		}

		if (IATriggerRightTrackpakR)
		{
			InEnhancedInputComponent->BindAction(IATriggerRightTrackpakR, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerRightTrackpakR);
		}

		if (IATriggerRightTrackpakUP)
		{
			InEnhancedInputComponent->BindAction(IATriggerRightTrackpakUP, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerRightTrackpakUPStart);
			InEnhancedInputComponent->BindAction(IATriggerRightTrackpakUP, ETriggerEvent::Completed, this, &AShooterVRPlayerController::TriggerRightTrackpakUPEnd);
		}

		if (IATriggerLeftTrackpakUP)
		{
			InEnhancedInputComponent->BindAction(IATriggerLeftTrackpakUP, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerLeftTrackpakUPStart);
			InEnhancedInputComponent->BindAction(IATriggerLeftTrackpakUP, ETriggerEvent::Completed, this, &AShooterVRPlayerController::TriggerLeftTrackpakUPEnd);
		}

		if (IATriggerLeftTrackpakD)
		{
			InEnhancedInputComponent->BindAction(IATriggerLeftTrackpakD, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::TriggerLeftTrackpakD);
		}

		if (IAGrabLeft)
		{
			InEnhancedInputComponent->BindAction(IAGrabLeft, ETriggerEvent::Started, this, &AShooterVRPlayerController::GrabLeftStart);
			InEnhancedInputComponent->BindAction(IAGrabLeft, ETriggerEvent::Completed, this, &AShooterVRPlayerController::GrabLeftEnd);
		}

		if (IAMenuLeft)
		{
			InEnhancedInputComponent->BindAction(IAMenuLeft, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::MenuLeftStart);
			InEnhancedInputComponent->BindAction(IAMenuLeft, ETriggerEvent::Completed, this, &AShooterVRPlayerController::MenuLeftEnd);
		}

		if (IAGrabRight)
		{
			InEnhancedInputComponent->BindAction(IAGrabRight, ETriggerEvent::Started, this, &AShooterVRPlayerController::GrabRightStart);
			InEnhancedInputComponent->BindAction(IAGrabRight, ETriggerEvent::Completed, this, &AShooterVRPlayerController::GrabRightEnd);
		}

		if (IAMenuRight)
		{
			InEnhancedInputComponent->BindAction(IAMenuRight, ETriggerEvent::Triggered, this, &AShooterVRPlayerController::MenuRightStart);
			InEnhancedInputComponent->BindAction(IAMenuRight, ETriggerEvent::Completed, this, &AShooterVRPlayerController::MenuRightEnd);
		}
	}
}

void AShooterVRPlayerController::AddInputMappingContext(TObjectPtr<UInputMappingContext> InInputMappingContext, int32 Priority)
{
	if (InInputMappingContext)
	{
		if (UEnhancedInputLocalPlayerSubsystem* InSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			InSubsystem->AddMappingContext(InInputMappingContext,Priority);
		}
	}
}

void AShooterVRPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);


}

void AShooterVRPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AddInputMappingContext(IMCDefaultGamepadContext);
}

void AShooterVRPlayerController::TriggerLeft(const FInputActionValue& InInputValue)
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("TriggerLeft"));
	//}
}

void AShooterVRPlayerController::TriggerLeftTrackpakL(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->MoveRight(-1.f);
	}
}

void AShooterVRPlayerController::TriggerLeftTrackpakR(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->MoveRight(1.f);
	}
}

void AShooterVRPlayerController::TriggerLeftTrackpakUPStart(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->MoveForward(1.f);
	}
}

void AShooterVRPlayerController::TriggerLeftTrackpakUPEnd(const FInputActionValue& InInputValue)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("TriggerLeftTrackpakUPEnd"));
	}
}

void AShooterVRPlayerController::TriggerLeftTrackpakD(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->MoveForward(-1.f);
	}
}

void AShooterVRPlayerController::GrabLeftStart(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->GrabLeftPressed();
	}
}

void AShooterVRPlayerController::GrabLeftEnd(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->GrabLeftReleased();
	}
}

void AShooterVRPlayerController::MenuLeftStart(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->LeftDrag();
	}
}

void AShooterVRPlayerController::MenuLeftEnd(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->LeftDragEnd();
	}
}

void AShooterVRPlayerController::TriggerRight(const FInputActionValue& InInputValue)
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("TriggerRight"));
	//}
}

void AShooterVRPlayerController::TriggerRightTrackpakL(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->SnapTurn(false);
	}
}

void AShooterVRPlayerController::TriggerRightTrackpakR(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->SnapTurn(true);
	}
}

void AShooterVRPlayerController::TriggerRightTrackpakUPStart(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->StartTeleportTrace();
		InCharacter->TeleportTrace();
	}
}

void AShooterVRPlayerController::TriggerRightTrackpakUPEnd(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->EndTeleportTrace();

		InCharacter->TryTeleport();
	}
}

void AShooterVRPlayerController::GrabRightStart(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->GrabRightPressed();
	}
}

void AShooterVRPlayerController::GrabRightEnd(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->GrabRightReleased();
	}
}

void AShooterVRPlayerController::MenuRightStart(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->RightDrag();
	}
}

void AShooterVRPlayerController::MenuRightEnd(const FInputActionValue& InInputValue)
{
	if (AShooterVRCharacter* InCharacter = GetPawn<AShooterVRCharacter>())
	{
		InCharacter->RightDragEnd();
	}
}

void AShooterVRPlayerController::RemoveInputMappingContext(TObjectPtr<UInputMappingContext> InInputMappingContext)
{
	if (InInputMappingContext)
	{
		if (UEnhancedInputLocalPlayerSubsystem* InSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			InSubsystem->RemoveMappingContext(InInputMappingContext);
		}
	}
}