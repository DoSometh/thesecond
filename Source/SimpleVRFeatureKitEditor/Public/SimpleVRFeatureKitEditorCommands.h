// Copyright (C) RenZhai.2025.All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "SimpleVRFeatureKitEditorStyle.h"

class FSimpleVRFeatureKitEditorCommands : public TCommands<FSimpleVRFeatureKitEditorCommands>
{
public:

	FSimpleVRFeatureKitEditorCommands()
		: TCommands<FSimpleVRFeatureKitEditorCommands>(TEXT("SimpleVRFeatureKitEditor"), NSLOCTEXT("Contexts", "SimpleVRFeatureKitEditor", "SimpleVRFeatureKitEditor Plugin"), NAME_None, FSimpleVRFeatureKitEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
