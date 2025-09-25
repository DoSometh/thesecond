
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
				//ע��Hit
				if (bFromSweep)
				{
					InTarget->SetHitResult(SweepResult);
				}

				if (!InTarget->IsDie() && //�ж���ɫ�Ƿ��Ѿ�����
					!IsExist(InTarget))//�Ƿ��Ѿ������˺�
				{
					//������ʵ���˺�
					if (GetWorld()->IsNetMode(ENetMode::NM_DedicatedServer) ||
						GetWorld()->IsNetMode(ENetMode::NM_Standalone) ||
						GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
					{
						FGameplayEventData EventData;
						EventData.Instigator = GetInstigator();
						EventData.Target = InTarget;

						if (!Buffs.IsEmpty())
						{
							//ִ��buff AE
							for (auto& Tmp : Buffs)
							{
								//�����ϵĴ��� ����
								UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
									GetScapegoatActor(),
									FGameplayTag::RequestGameplayTag(Tmp),
									EventData);
							}
						}
						else if (!BuffTags.IsEmpty()) //BuffTags
						{
							//ִ��buff AE
							for (auto& Tmp : BuffTags)
							{
								//�����ϵĴ��� ����
								UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
									GetScapegoatActor(),
									Tmp,
									EventData);
							}
						}

					}

					//�ͻ��˵ı��� �����ܻ� �ܻ���Ч��
					if (GetWorld()->IsNetMode(ENetMode::NM_Client) ||
						GetWorld()->IsNetMode(ENetMode::NM_Standalone) ||
						GetWorld()->IsNetMode(ENetMode::NM_ListenServer))
					{

					}
				}

				//ע���Ѿ����еĶ��� ��ֹ���λ���
				Super::HandleDamage(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
				
				InTarget->ClearHitResult();

				Destroyed();
			}
		}
	}
}