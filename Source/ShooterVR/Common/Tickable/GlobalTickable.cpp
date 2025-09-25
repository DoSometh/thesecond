//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "GlobalTickable.h"


FGlobalTickable* FGlobalTickable::Instance = NULL;

FGlobalTickable* FGlobalTickable::Get()
{
	if (!Instance)
	{
		Instance = new FGlobalTickable();
	}

	return Instance;
}

void FGlobalTickable::Destroy()
{
	if (Instance)
	{
		delete Instance;
	}

	Instance = NULL;
}

void FGlobalTickable::Tick(float DeltaTime)
{

}

TStatId FGlobalTickable::GetStatId() const
{
	return TStatId();
}