#include "NS_Light.h"

#include "Kismet/GameplayStatics.h"

ANS_Light::ANS_Light()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANS_Light::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANS_Light::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// TODO - This is a temporary solution, to be replaced with a more robust system
	if (PlayerLightAwareEntityComponent == nullptr)
	{
		// Get player character
		ACharacter* UnrealCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		PlayerCharacter = Cast<ACharacterBase>(UnrealCharacter);

		PlayerLightAwareEntityComponent = PlayerCharacter->LightAwareEntityComponent;
	}

	CompareToPlayer();
}

bool ANS_Light::IsInSightOfPlayer(FHitResult& OutHit)
{
	return false;
}

void ANS_Light::CompareToPlayer()
{
	FHitResult Hit;
	const bool bIsInSight = IsInSightOfPlayer(Hit);
	
	if (bIsInSight) PlayerLightAwareEntityComponent->AddLightInSight(this);
	else PlayerLightAwareEntityComponent->RemoveLightInSight(this);
}