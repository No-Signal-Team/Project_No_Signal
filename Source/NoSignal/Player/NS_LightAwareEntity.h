#pragma once

#include "NS_LightAwareEntity.generated.h"

UCLASS()
class NOSIGNAL_API UNS_LightAwareEntity : public UActorComponent
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
	
	TSet<AActor*> &GetLightsInSight() { return LightsInSight; }
	
	int GetNbLightsInSight() const { return LightsInSight.Num(); }

	void AddLightInSight(AActor* Light) { LightsInSight.Add(Light); }

	void RemoveLightInSight(AActor* Light) { LightsInSight.Remove(Light); }

	void UpdateState();

protected:
	
	UPROPERTY(EditAnywhere)
	TSet<AActor*> LightsInSight;
	
};
