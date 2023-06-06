#include "NS_Light.h"

#include "Kismet/GameplayStatics.h"

ANS_Light::ANS_Light()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANS_Light::BeginPlay()
{
	Super::BeginPlay();
	
	// Get player character
	ACharacter* UnrealCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerCharacter = Cast<ACharacterBase>(UnrealCharacter);

	PlayerLightAwareEntityComponent = PlayerCharacter->LightAwareEntityComponent;
	
}

void ANS_Light::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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