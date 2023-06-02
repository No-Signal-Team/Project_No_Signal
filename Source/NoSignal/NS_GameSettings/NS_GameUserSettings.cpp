// Fill out your copyright notice in the Description page of Project Settings.


#include "NS_GameUserSettings.h"

UNS_GameUserSettings* UNS_GameUserSettings::GetNSUserSettings()
{
	return Cast<UNS_GameUserSettings>(GetGameUserSettings());
}