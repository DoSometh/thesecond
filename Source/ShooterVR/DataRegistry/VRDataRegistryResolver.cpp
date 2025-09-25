#include "VRDataRegistryResolver.h"
#include "DataRegistrySource.h"

bool FVRDataRegistryResolver::ResolveIdToName(
	FName& OutResolvedName, 
	const FDataRegistryId& ItemId, 
	const UDataRegistry* Registry,const UDataRegistrySource* RegistrySource)
{
	TArray<FName> OutNames;
	RegistrySource->GetResolvedNames(OutNames);

	FString NameString = ItemId.ItemName.ToString();
	if (NameString.IsNumeric())
	{
		int32 Index = FCString::Atoi(*NameString);
		if (OutNames.IsValidIndex(Index))
		{
			OutResolvedName = OutNames[Index];

			return true;
		}
	}

	return false;
}
