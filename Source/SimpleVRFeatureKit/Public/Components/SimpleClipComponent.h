#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Components/BoxComponent.h"
#include "SimpleClipComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SIMPLEVRFEATUREKIT_API USimpleClipComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	USimpleClipComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};