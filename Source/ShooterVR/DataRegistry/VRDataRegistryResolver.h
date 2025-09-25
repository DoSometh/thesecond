//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "DataRegistryTypes.h"

struct FVRDataRegistryResolver :public FDataRegistryResolver
{
	/** Override this function, if it returns true then OutResolvedName should be used, otherwise will check other resolvers and default behavior */
	virtual bool ResolveIdToName(FName& OutResolvedName, const FDataRegistryId& ItemId, const class UDataRegistry* Registry, const class UDataRegistrySource* RegistrySource);
};

