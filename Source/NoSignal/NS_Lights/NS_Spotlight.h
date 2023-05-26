// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SpotLightComponent.h"
#include "GameFramework/Actor.h"
#include "NoSignal/CharacterBase.h"
#include "NS_Spotlight.generated.h"

UCLASS()
class NOSIGNAL_API ANS_Spotlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANS_Spotlight();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsInSightOfPlayer(FHitResult& OutHit);

	void CompareToPlayer();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USpotLightComponent* Spotlight;

	ACharacterBase* PlayerCharacter;

};
