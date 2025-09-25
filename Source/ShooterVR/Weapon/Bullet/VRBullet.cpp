
#include "VRBullet.h"
#include "../../Framework/Core/FrameworkCharacterBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags.h"

AVRBullet::AVRBullet(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void AVRBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AVRBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVRBullet::HandleDamage(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (GetInstigator() != OtherActor)
	{
		if (AFrameworkCharacterBase* InPawn = Cast<AFrameworkCharacterBase>(GetInstigator()))
		{
			if (AFrameworkCharacterBase* InTarget = Cast<AFrameworkCharacterBase>(OtherActor))
			{
				//注册Hit
				if (bFromSweep)
				{
					InTarget->SetHitResult(SweepResult);
				}

				if (!InTarget->IsDie() && //判定角色是否已经死亡
					!IsExist(InTarget))//是否已经给过伤害
				{
					//计算真实的伤害
					if (GetWorld()->IsNetMode(ENetMode::NM_DedicatedServer) ||
						GetWorld()->IsNetMode(ENetMode::NM_Standalone) ||
						GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
					{
						FGameplayEventData EventData;
						EventData.Instigator = GetInstigator();
						EventData.Target = InTarget;

						if (!Buffs.IsEmpty())
						{
							//执行buff AE
							for (auto& Tmp : Buffs)
							{
								//数据上的处理 受伤
								UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
									GetScapegoatActor(),
									FGameplayTag::RequestGameplayTag(Tmp),
									EventData);
							}
						}
						else if (!BuffTags.IsEmpty()) //BuffTags
						{
							//执行buff AE
							for (auto& Tmp : BuffTags)
							{
								//数据上的处理 受伤
								UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
									GetScapegoatActor(),
									Tmp,
									EventData);
							}
						}

					}

					//客户端的表现 比如受击 受击特效等
					if (GetWorld()->IsNetMode(ENetMode::NM_Client) ||
						GetWorld()->IsNetMode(ENetMode::NM_Standalone) ||
						GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
					{

					}
				}

				//注册已经击中的对象 防止二次击中
				Super::HandleDamage(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
				
				InTarget->ClearHitResult();

				Destroyed();
			}
		}
	}
}