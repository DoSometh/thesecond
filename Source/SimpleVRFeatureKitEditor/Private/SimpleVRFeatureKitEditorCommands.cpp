// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "SimpleVRFeatureKitEditorCommands.h"

#define LOCTEXT_NAMESPACE "FSimpleVRFeatureKitEditorModule"

void FSimpleVRFeatureKitEditorCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "SimpleVRFeatureKitEditor", "Execute SimpleVRFeatureKitEditor action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
