// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "Actor/SimpleInsertExtractActor.h"
#include "Components/SimpleInsertExtractComponent.h"
#include "Components/BoxComponent.h"

ASimpleInsertExtractActor::ASimpleInsertExtractActor()
{
	InsertExtractRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("InsertExtractRootComponent"));
	SetRootComponent(InsertExtractRootComponent);

	InsertExtractComponent = CreateDefaultSubobject<USimpleInsertExtractComponent>(TEXT("InsertExtractComponent"));
	InsertExtractComponent->SetupAttachment(RootComponent);
}

void ASimpleInsertExtractActor::PreInit()
{

}

void ASimpleInsertExtractActor::PostInit()
{

}

void ASimpleInsertExtractActor::Start(const FInsertExtractInfo& InInsertExtractInfo,const FVector& InImpactNormal)
{
	InsertExtractComponent->Start(InInsertExtractInfo, InImpactNormal);
}

void ASimpleInsertExtractActor::End()
{
	InsertExtractComponent->End();
}

void ASimpleInsertExtractActor::Registration(UMotionControllerComponent* InMotionControllerComponent, USceneComponent* InHand)
{
	InsertExtractComponent->Registration(InMotionControllerComponent, InHand);
}

void ASimpleInsertExtractActor::Deregistration()
{
	InsertExtractComponent->Deregistration();
}

void ASimpleInsertExtractActor::BeginPlay()
{
	Super::BeginPlay();

}

void ASimpleInsertExtractActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ASimpleInsertExtractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}