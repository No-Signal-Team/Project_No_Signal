#pragma once

#include "GameFramework/Actor.h"
#include "NoSignal/CharacterBase.h"
#include "NS_Light.generated.h"

UCLASS(Abstract)
class NOSIGNAL_API ANS_Light : public AActor
{
	GENERATED_BODY()
	
public:
	ANS_Light();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Check if the player is in the spotlight's cone
	virtual bool IsInSightOfPlayer(FHitResult& OutHit);

	// Checks if the spotlight is in the player's cone
	virtual void CompareToPlayer();

protected:
	ACharacterBase* PlayerCharacter;

	UNS_LightAwareEntity* PlayerLightAwareEntityComponent;
	
};
