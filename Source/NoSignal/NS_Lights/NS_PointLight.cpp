#include "NS_PointLight.h"

ANS_PointLight::ANS_PointLight() : ANS_Light()
{
	// Get the spotlight actor from the blueprint
	PointLight = CreateDefaultSubobject<UPointLightComponent>("Spotlight");
	PointLight->SetupAttachment(RootComponent);
}

bool ANS_PointLight::IsInSightOfPlayer(FHitResult& OutHit)
{
	if (!PlayerCharacter || !PointLight) return false;
	
	// Raycast
	const FVector Start = PointLight->GetComponentLocation();
	const FVector End = PlayerCharacter->GetActorLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	const bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params);
	
	// Get distance
	const float Distance = (Start - End).Size();
	const bool bCloseEnough = Distance <= PointLight->AttenuationRadius;
	
	return !bHit && bCloseEnough;
}