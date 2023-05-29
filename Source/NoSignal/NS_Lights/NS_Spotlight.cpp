// Fill out your copyright notice in the Description page of Project Settings.


#include "NS_Spotlight.h"

#include "Components/SpotLightComponent.h"

// Sets default values
ANS_Spotlight::ANS_Spotlight() : ANS_Light()
{
	// Get the spotlight actor from the blueprint
	Spotlight = CreateDefaultSubobject<USpotLightComponent>("Spotlight");
	Spotlight->SetupAttachment(RootComponent);
}

bool ANS_Spotlight::IsInSightOfPlayer(FHitResult& OutHit)
{
	if (!PlayerCharacter || !Spotlight) return false;
	
	// Raycast
	const FVector Start = Spotlight->GetComponentLocation();
	const FVector End = PlayerCharacter->GetActorLocation();
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	const bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params);
	
	// Get distance
	const float Distance = (Start - End).Size();
	const bool bCloseEnough = Distance <= Spotlight->AttenuationRadius;
	
	// Check that the player is inside the spotlight's cone
	const FVector Direction = (End - Start).GetSafeNormal();
	const float ConeAngle = FMath::DegreesToRadians(Spotlight->OuterConeAngle);
	const float DotProduct = FVector::DotProduct(Direction, Spotlight->GetForwardVector());
	const bool bInCone = DotProduct >= FMath::Cos(ConeAngle);
	
	return !bHit && bCloseEnough && bInCone;
}


