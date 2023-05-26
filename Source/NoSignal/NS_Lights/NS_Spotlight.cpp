// Fill out your copyright notice in the Description page of Project Settings.


#include "NS_Spotlight.h"

#include "Components/SpotLightComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANS_Spotlight::ANS_Spotlight()
{
	// Get the spotlight actor from the blueprint
	Spotlight = CreateDefaultSubobject<USpotLightComponent>("Spotlight");
	Spotlight->SetupAttachment(RootComponent);
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANS_Spotlight::BeginPlay()
{
	Super::BeginPlay();
	
	// Get player character
	PlayerCharacter = Cast<ACharacterBase>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ANS_Spotlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult Hit;
	if (IsInSightOfPlayer(Hit)) CompareToPlayer();
}

bool ANS_Spotlight::IsInSightOfPlayer(FHitResult& OutHit)
{
	if (!PlayerCharacter || !Spotlight) return false;
	UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter: %s"), *PlayerCharacter->GetName());
	
	// Raycast
	const FVector Start = Spotlight->GetComponentLocation();
	const FVector End = PlayerCharacter->GetActorLocation();
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	const bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, Params);
	
	// Get distance
	const float Distance = (Start - End).Size();
	const bool bCloseEnough = Distance <= Spotlight->AttenuationRadius;

	//Log raycast and distance
	UE_LOG(LogTemp, Warning, TEXT("Raycast: %s, Distance: %f"), bHit ? TEXT("true") : TEXT("false"), Distance);
	
	return !bHit && bCloseEnough;
}

void ANS_Spotlight::CompareToPlayer()
{
	TSet<AActor*> LightsInSight = PlayerCharacter->lightAwareEntityComponent->GetLightsInSight();
	bool bContainsLight = LightsInSight.Contains(this);

	if (bContainsLight) LightsInSight.Add(this);
	else LightsInSight.Remove(this);
}

