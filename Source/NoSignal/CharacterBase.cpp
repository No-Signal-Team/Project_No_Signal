// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include <Engine/Classes/Camera/CameraComponent.h>
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>

#include "Kismet/GameplayStatics.h"
#include "NS_Lights/NS_PointLight.h"
#include "NS_Lights/NS_Spotlight.h"

// Sets default values
ACharacterBase::ACharacterBase()
	: WalkSpeed(200.0F), RunSpeed(800.0F)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraComponent->SetupAttachment(GetCapsuleComponent());
	cameraComponent->bUsePawnControlRotation = true;

	LightAwareEntityComponent = CreateDefaultSubobject<UNS_LightAwareEntity>("LightAwareEntity");
	AddOwnedComponent(LightAwareEntityComponent);

	StressInfluencedEntityComponent = CreateDefaultSubobject<UNS_StressInfluencedEntity>("StressInfluencedEntity");
	AddOwnedComponent(StressInfluencedEntityComponent);

	this->GetCharacterMovement()->BrakingDecelerationWalking = 128.0F;
	this->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterBase::MoveForward(float axis)
{
	AddMovementInput(GetActorForwardVector(), axis);
}

void ACharacterBase::MoveRight(float axis)
{
	AddMovementInput(GetActorRightVector(), axis);
}

void ACharacterBase::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void ACharacterBase::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UpdateStressAmount(DeltaTime);
	UpdateStressState();
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterBase::MoveRight);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ACharacterBase::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ACharacterBase::EndSprint);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void ACharacterBase::UpdateStressAmount(const float Dt)
{
	float StressFactor = MaxStressFactor;

	// For each light in sight, compute the stress factor.
	// The stress factor is computed by the distance between the light and the character.
	for (AActor* Light : LightAwareEntityComponent->GetLightsInSight())
	{
		FVector Distance = GetActorLocation() - Light->GetActorLocation();
		float Slope = 0.0F;

		if (const ANS_Spotlight* Sp = Cast<ANS_Spotlight>(Light))
		{
			Slope = 0.01F * (Distance.Length() - Sp->GetSpotlightComponent()->AttenuationRadius) * 0.01F;
		}
		else if (const ANS_PointLight* Pl = Cast<ANS_PointLight>(Light))
		{
			Slope = 0.01F * (Distance.Length() - Pl->GetPointLightComponent()->AttenuationRadius) * 0.01F;
		}
		else UE_LOG(LogTemp, Error, TEXT("Light type not supported"));
		
		StressFactor += Slope;
	}

	StressFactor = FMath::Clamp(StressFactor, MinStressFactor, MaxStressFactor);
	StressFactor *= Dt;
	StressInfluencedEntityComponent->SetStressAmount(StressFactor);
}

void ACharacterBase::UpdateStressState()
{
	cameraComponent->PostProcessSettings.bOverride_SceneFringeIntensity = true;
	cameraComponent->PostProcessSettings.SceneFringeIntensity =
		StressInfluencedEntityComponent->GetStressAmount() * MaxAberration;
}
