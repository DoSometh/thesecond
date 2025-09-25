//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"


//主要为了游戏中需要被单独tick的 单例tick 如果在项目里面 多个客户端可能会同一帧tick该单例
class FGlobalTickable :public FTickableGameObject
{
public:
	static FGlobalTickable* Get();
	static void Destroy();
public:
	virtual void Tick(float DeltaTime);

	virtual TStatId GetStatId() const;

private:

	static FGlobalTickable* Instance;
};