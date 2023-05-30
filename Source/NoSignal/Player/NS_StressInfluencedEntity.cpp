#include "NS_StressInfluencedEntity.h"

#include "Kismet/GameplayStatics.h"

void UNS_StressInfluencedEntity::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(GetWorld(), StressSound, StressAmount);
	
}

void UNS_StressInfluencedEntity::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

void UNS_StressInfluencedEntity::SetStressAmount(const float Sa)
{
	StressAmount = FMath::Clamp(StressAmount+Sa, Min_Stress, Max_Stress);
}


