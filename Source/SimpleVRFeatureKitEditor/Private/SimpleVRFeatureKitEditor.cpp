// Copyright (C) RenZhai.2025.All Rights Reserved.

#include "SimpleVRFeatureKitEditor.h"
#include "SimpleVRFeatureKitEditorStyle.h"
#include "SimpleVRFeatureKitEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "ISettingsModule.h"
#include "Settings/SimpleVRFeatureKitSettings.h"

static const FName SimpleVRFeatureKitEditorTabName("SimpleVRFeatureKitEditor");

#define LOCTEXT_NAMESPACE "FSimpleVRFeatureKitEditorModule"

void FSimpleVRFeatureKitEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FSimpleVRFeatureKitEditorStyle::Initialize();
	FSimpleVRFeatureKitEditorStyle::ReloadTextures();

	FSimpleVRFeatureKitEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	//注册设置
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>(TEXT("Settings")))
	{
		SettingsModule->RegisterSettings("Project",
			"SimpleVRFeatureKit",
			"SimpleVRFeatureKitSettings",
			LOCTEXT("SimpleVRFeatureKitSettings", "VR Kit Settings"),
			LOCTEXT("SimpleVRFeatureKitSettingsTip", "VR kit related settings."),
			GetMutableDefault<USimpleVRFeatureKitSettings>());
	}
}

void FSimpleVRFeatureKitEditorModule::ShutdownModule()
{
	FSimpleVRFeatureKitEditorStyle::Shutdown();

	FSimpleVRFeatureKitEditorCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleVRFeatureKitEditorModule, SimpleVRFeatureKitEditor)