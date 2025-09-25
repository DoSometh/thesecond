// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterVRGameStateBase.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Core/FrameworkCharacterBase.h"
#include "../Weapon/Core/VRWeaponBase.h"
#include "../AbilitiesSystem/AttributeSet/VRShooterAttributeSet.h"
#include "../DataRegistry/VRDataRegistryManage.h"

AShooterVRGameStateBase::AShooterVRGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAttributeTable(TEXT("/Game/DataTable/CharacterAttributeTable"));
	CharacterAttributeTablePtr = CharacterAttributeTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> GunAttributeTable(TEXT("/Game/DataTable/Weapon/GunAttribute"));
	GunAttributeTablePtr = GunAttributeTable.Object;
}

void AShooterVRGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	VRDragManage.Tick(DeltaTime);
}

FGunAttributeTable* AShooterVRGameStateBase::GetGunAttributeTable(int32 InID)
{
	return GetTable(InID, GunAttributeTablePtr, GunAttributeTables,TEXT("Gun"));
}

TArray<FGunAttributeTable*>* AShooterVRGameStateBase::GetGunAttributeTables()
{
	return GetTables(GunAttributeTablePtr, GunAttributeTables);
}

FCharacterAttributeTable* AShooterVRGameStateBase::GetCharacterAttributeTable(int32 InID)
{
	return GetTable(InID, CharacterAttributeTablePtr, CharacterAttributeTables, TEXT("Character"));
}

TArray<FCharacterAttributeTable*>* AShooterVRGameStateBase::GetCharacterAttributeTables()
{
	return GetTables(CharacterAttributeTablePtr, CharacterAttributeTables);
}

bool AShooterVRGameStateBase::RegistrationAFrameworkCharacter(AFrameworkCharacterBase* InCharacter)
{
	if (InCharacter)
	{
		if (UVRShooterAttributeSet* InAttribute = InCharacter->GetAttribute())
		{
			if (FCharacterAttributeTable* InAttributeTable = GetCharacterAttributeTable(InCharacter->GetID()))
			{
				InAttribute->RegistrationProperties(InAttributeTable);

				return true;
			}
		}
	}

	return false;
}

bool AShooterVRGameStateBase::RegistrationAFrameworkCharacter(AVRWeaponBase* InWeapon)
{
	if (InWeapon)
	{
		if (UVRAttributeSetBase* InAttribute = InWeapon->GetAttribute())
		{
			if (FGunAttributeTable* InAttributeTable = GetGunAttributeTable(InWeapon->GetID()))
			{
				InAttribute->RegistrationProperties(InAttributeTable);

				return true;
			}
		}
	}

	return false;
}

void AShooterVRGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	//зЂВс
	FVRDataRegistryManage::Get();
}