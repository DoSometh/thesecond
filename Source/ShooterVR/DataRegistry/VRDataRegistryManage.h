//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "ShooterVR/DataTable/Voice/VoiceTable.h"
#include "ShooterVR/DataTable/Effect/EffectTable.h"
#include "DataRegistrySubsystem.h"

class FVRDataRegistryManage
{
public:
	static FVRDataRegistryManage* Get();
	static void Destroy();

protected:
	virtual void Structure();
	virtual void Deconstruction();
public:
	void RegisterVRDataRegistryResolver();
	
	const FVoiceTable* FindVoiceCached(EVRHitType InHitType);
	const FEffectTable* FindEffectCached(EVRHitType InHitType);
protected:
	template<class T>
	const T* FindCached(FName InRegisterType, EVRHitType InType);

private:
	static FVRDataRegistryManage *VRDataRegistryManage;
};

template<class T>
const T* FVRDataRegistryManage::FindCached(FName InRegisterType, EVRHitType InType)
{
	if (UDataRegistrySubsystem* Subsystem = GEngine->GetEngineSubsystem<UDataRegistrySubsystem>())
	{
		FDataRegistryId RegistryId;
		RegistryId.ItemName = *FString::FromInt((int32)InType);
		RegistryId.RegistryType = InRegisterType;

		return Subsystem->GetCachedItem<T>(RegistryId);
	}

	return nullptr;
};