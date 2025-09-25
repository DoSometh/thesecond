#include "VRDataRegistryManage.h"
#include "VRDataRegistryResolver.h"

static const FName DR_SoundEffect = FName(TEXT("DR_SoundEffect"));
static const FName DR_Effect = FName(TEXT("DR_Effect"));

FVRDataRegistryManage* FVRDataRegistryManage::VRDataRegistryManage = NULL;

FVRDataRegistryManage* FVRDataRegistryManage::Get()
{
	if (!VRDataRegistryManage)
	{
		VRDataRegistryManage = new FVRDataRegistryManage();
		VRDataRegistryManage->Structure();
	}

	return VRDataRegistryManage;
}

void FVRDataRegistryManage::Destroy()
{
	if (VRDataRegistryManage)
	{
		VRDataRegistryManage->Deconstruction();

		delete VRDataRegistryManage;	
	}

	VRDataRegistryManage = NULL;
}

void FVRDataRegistryManage::Structure()
{
	VRDataRegistryManage->RegisterVRDataRegistryResolver();
}

void FVRDataRegistryManage::Deconstruction()
{

}

void FVRDataRegistryManage::RegisterVRDataRegistryResolver()
{
	FDataRegistryResolverScope::RegisterGlobalResolver(MakeShareable(new FVRDataRegistryResolver()));
}

const FVoiceTable* FVRDataRegistryManage::FindVoiceCached(EVRHitType InHitType)
{
	return FindCached<FVoiceTable>(DR_SoundEffect, InHitType);
}

const FEffectTable* FVRDataRegistryManage::FindEffectCached(EVRHitType InHitType)
{
	return FindCached<FEffectTable>(DR_Effect, InHitType);
}
