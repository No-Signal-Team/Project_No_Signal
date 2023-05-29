#include "NS_StressInfluencedEntity.h"

void UNS_StressInfluencedEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

void UNS_StressInfluencedEntity::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UNS_StressInfluencedEntity::AddStress(const float Sa)
{
	const float SupposedStressAmount = this->StressAmount + Sa;
	
	if (SupposedStressAmount > Max_Stress) this->StressAmount = Max_Stress;
	else this->StressAmount = SupposedStressAmount;
}

void UNS_StressInfluencedEntity::RemoveStress(const float Sa)
{
	const float SupposedStressAmount = this->StressAmount - Sa;

	if (SupposedStressAmount < 0.f) this->StressAmount = 0.f;
	else this->StressAmount = SupposedStressAmount;
}

