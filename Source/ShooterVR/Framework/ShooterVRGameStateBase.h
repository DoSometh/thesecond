// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleModularGameState.h"
#include "Drag/VRDragItemManage.h"
#include "../DataTable/Attribute/CharacterAttributeTable.h"
#include "../DataTable/Attribute/Weapon/GunAttributeTable.h"
#include "ShooterVRGameStateBase.generated.h"

class AFrameworkCharacterBase;
class AVRWeaponBase;
/**
 * 
 */
UCLASS()
class SHOOTERVR_API AShooterVRGameStateBase : public ASimpleModularGameStateBase
{
	GENERATED_BODY()

public:
	AShooterVRGameStateBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	//枪的数据
	FGunAttributeTable* GetGunAttributeTable(int32 InID);
	TArray<FGunAttributeTable*>* GetGunAttributeTables();

	//角色的数据
	FCharacterAttributeTable* GetCharacterAttributeTable(int32 InID);
	TArray<FCharacterAttributeTable*>* GetCharacterAttributeTables();

public:
	bool RegistrationAFrameworkCharacter(AFrameworkCharacterBase *InCharacter);
	bool RegistrationAFrameworkCharacter(AVRWeaponBase* InCharacter);

public:
	UPROPERTY()
	FVRDragItemManage VRDragManage;

protected:
	UPROPERTY()
	UDataTable* GunAttributeTablePtr;

	UPROPERTY()
	UDataTable* CharacterAttributeTablePtr;

	TArray<FGunAttributeTable*> GunAttributeTables;
	TArray<FCharacterAttributeTable*> CharacterAttributeTables;

protected:
	//获取所有的Table数据
	template<class T>
	TArray<T*>* GetTables(
		UDataTable* InTable,
		TArray<T*>& OutTables,
		const FString& MsgTag = TEXT("MyTables"))
	{
		if (!OutTables.Num())
		{
			if (InTable)
			{
				InTable->GetAllRows(MsgTag, OutTables);
			}
		}

		return &OutTables;
	}

	//获取单个的Table数据
	template<class T>
	T* GetTable(
		int32 InTableID,
		UDataTable* InTable,
		TArray<T*>& OutTables,
		const FString& MsgTag = TEXT("MyTable"))
	{
		if (TArray<T*>* InTables = GetTables<T>(InTable, OutTables, MsgTag))
		{
			if (InTables->Num())
			{
				if (auto InMyTable = InTables->FindByPredicate([&](T* InMyTable) {return InMyTable->ID == InTableID; }))
				{
					return *InMyTable;
				}
			}
		}

		return NULL;
	}
};
