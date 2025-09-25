// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "SimpleVRFeatureKitType.h"
#include "Interface/VRGrabInterface.h"

FSimpleGrabLockInfo::FSimpleGrabLockInfo()
{
	Clear();
}

void FSimpleGrabLockInfo::Clear()
{
	AGrabInterface = NULL;
	BGrabInterface = NULL;

	GrabLockState = ESimpleGrabLockState::GRABLOCK_NONE;
}

bool FSimpleGrabLockInfo::IsValid() const
{
	return 	AGrabInterface &&
			BGrabInterface &&
			AGrabInterface->GetMotionController() &&
			BGrabInterface->GetMotionController();
}

FSimpleTouchControlIncremental::FSimpleTouchControlIncremental()
	:ReferenceCount(0)
	, MaxRotation(FRotator(180.f))
	, MinRotation(FRotator(-180.f))
	, MaxPosition(FVector(999999.f))
	, MinPosition(FVector(-999999.f))
{

}

FSimpleTouchControlInfo::FSimpleTouchControlInfo()
	:IncrementalPtr(NULL)
{

}

FInsertExtractInfo::FInsertExtractInfo()
{
	InsertDirection = FVector::ZeroVector;
	Extend = FVector(32.f);
	LengthOffset = 5.f;
}

FVRClimbInfo::FVRClimbInfo()
	:HandleID(INDEX_NONE)
{

}
