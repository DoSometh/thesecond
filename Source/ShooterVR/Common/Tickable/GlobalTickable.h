//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"


//��ҪΪ����Ϸ����Ҫ������tick�� ����tick �������Ŀ���� ����ͻ��˿��ܻ�ͬһ֡tick�õ���
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