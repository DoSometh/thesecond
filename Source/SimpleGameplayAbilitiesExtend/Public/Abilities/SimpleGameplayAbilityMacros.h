//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#define PROPERTY_FUNCTION_REGISTRATION(ClassName, PropertyName) \
	float Last##PropertyName; \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define CHECK_OWNING_ASC_GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue,String)\
if (GetOwningAbilitySystemComponent())\
{\
	GAMEPLAYATTRIBUTE_REPNOTIFY(ClassName, PropertyName, OldValue);}\
else\
{\
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, String);\
}

