//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "CombatInterface/SimpleCombatInterface.h"

// Add default functionality here for any ISimpleCombatInterface functions that are not pure virtual.

ISimpleComboInterface::ISimpleComboInterface()
{

}

void ISimpleComboInterface::Update_AttachPoint(const FSimpleAttachPointInfo& InValue, FName InTag, bool bEnd)
{
	//RWLock.TryWriteLock();

	if (!AttachPointAlpha.Contains(InTag))
	{
		AttachPointAlpha.Add(InTag);
	}
	
	AttachPointAlpha[InTag] = InValue;

	if (bEnd)
	{
		AttachPointAlpha[InTag].End();
	}
	else
	{
		AttachPointAlpha[InTag].Start();
	}
}

FSimpleAttachPointInfo ISimpleComboInterface::FindAttachPointInfo(FName InName)
{
	//RWLock.ReadLock();

	if (AttachPointAlpha.Contains(InName))
	{
		return AttachPointAlpha[InName];
	}

	return FSimpleAttachPointInfo();
}

void ISimpleComboInterface::TickDrive(float InNewTime)
{
	for (auto &Tmp : AttachPointAlpha)
	{
		Tmp.Value.Tick(InNewTime);
	}
}