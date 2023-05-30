﻿#pragma once

#include "NS_StressInfluencedEntity.generated.h"

UCLASS()
class UNS_StressInfluencedEntity : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	float GetStressAmount() const { return StressAmount; }

	void SetStressAmount(const float Sa);

	void ResetStress() { StressAmount = 0.f; }

private:

	UPROPERTY(VisibleAnywhere, Category = "Stress")
	float StressAmount;

	const float Max_Stress = 1.F;
	const float Min_Stress = 0.F;
};
