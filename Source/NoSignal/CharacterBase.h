// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player/NS_LightAwareEntity.h"
#include "Player/NS_StressInfluencedEntity.h"
#include "CharacterBase.generated.h"

class UCameraComponent;

UCLASS()
class NOSIGNAL_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ACharacterBase();



protected:

	virtual void BeginPlay() override;

	// Input callbacks.
	void MoveForward(float axis);
	void MoveRight(float axis);
	void BeginSprint();
	void EndSprint();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void UpdateStressAmount(float dt);
	void UpdateStressState();


public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UCameraComponent> cameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNS_LightAwareEntity> LightAwareEntityComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UNS_StressInfluencedEntity> StressInfluencedEntityComponent;
	
private:

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	UPROPERTY(EditAnywhere)
	float RunSpeed;

};
