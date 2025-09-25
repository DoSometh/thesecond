#include "ShooterVRFunctionLibrary.h"

UShooterVRFunctionLibrary::UShooterVRFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

bool UShooterVRFunctionLibrary::FindVoiceCached(EVRHitType InHitType, FVoiceTable& OutItem)
{
	if (const FVoiceTable* InVoiceTable = FVRDataRegistryManage::Get()->FindVoiceCached(InHitType))
	{
		OutItem = *InVoiceTable;

		return true;
	}

	return false;
}

bool UShooterVRFunctionLibrary::FindEffectCached(EVRHitType InHitType, FEffectTable& OutItem)
{
	if (const FEffectTable* InEffectTable = FVRDataRegistryManage::Get()->FindEffectCached(InHitType))
	{
		OutItem = *InEffectTable;

		return true;
	}

	return false;
}