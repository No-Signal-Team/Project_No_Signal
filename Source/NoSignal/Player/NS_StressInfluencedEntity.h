#pragma once

#include "NS_StressInfluencedEntity.generated.h"

UCLASS()
class UNS_StressInfluencedEntity : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	int GetStressAmount() const { return StressAmount; }

	void AddStress(float sa);

	void RemoveStress(float sa);

	void ResetStress() { StressAmount = 0.f; }

private:

	UPROPERTY(VisibleAnywhere, Category = "Stress")
	float StressAmount;

	const float Max_Stress = 100.f;

	// ACharacterBase* PlayerCharacter;
	
};
