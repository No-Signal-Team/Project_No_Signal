// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "NS_GameUserSettings.generated.h"

/**
 * This class is used to store user settings for our game.
 */
UCLASS()
class NOSIGNAL_API UNS_GameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:
	// Returns the current user settings.
	UFUNCTION(BlueprintCallable)
	static UNS_GameUserSettings* GetNSUserSettings();

	// The current Reticle color.
	UPROPERTY(Config, BlueprintReadWrite)
	FLinearColor ReticleColor;

	// The current Reticle opacity.
	UPROPERTY(Config, BlueprintReadWrite)
	float ReticleOpacity;
};
