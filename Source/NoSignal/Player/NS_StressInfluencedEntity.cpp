#include "NS_StressInfluencedEntity.h"
#include "Kismet/GameplayStatics.h"

#include "../CharacterBase.h"

void UNS_StressInfluencedEntity::BeginPlay()
{
	Super::BeginPlay();

	// PlayerCharacter = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void UNS_StressInfluencedEntity::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Log player number of lights
	// UE_LOG(LogTemp, Warning, TEXT("Player has %d lights in sight"), PlayerCharacter->lightAwareEntityComponent->GetLightsInSight().Num());
}

void UNS_StressInfluencedEntity::AddStress(float sa)
{
	const float SupposedStressAmount = this->StressAmount + StressAmount;
	
	if (SupposedStressAmount > Max_Stress) this->StressAmount = Max_Stress;
	else this->StressAmount = SupposedStressAmount;
}

void UNS_StressInfluencedEntity::RemoveStress(float sa)
{
	const float SupposedStressAmount = this->StressAmount - StressAmount;

	if (SupposedStressAmount < 0.f) this->StressAmount = 0.f;
	else this->StressAmount = SupposedStressAmount;
}

