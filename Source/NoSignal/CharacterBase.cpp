// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include <Engine/Classes/Camera/CameraComponent.h>
#include <Engine/Classes/Components/CapsuleComponent.h>
#include <Engine/Classes/GameFramework/CharacterMovementComponent.h>

// Sets default values
ACharacterBase::ACharacterBase()
	: WalkSpeed(200.0F), RunSpeed(800.0F)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	cameraComponent->SetupAttachment(GetCapsuleComponent());
	cameraComponent->bUsePawnControlRotation = true;

	lightAwareEntityComponent = CreateDefaultSubobject<UNS_LightAwareEntity>("LightAwareEntity");
	AddOwnedComponent(lightAwareEntityComponent);

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

void ACharacterBase::UpdateStressAmount(float dt)
{
}
