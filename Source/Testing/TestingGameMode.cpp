// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "TestingGameMode.h"
#include "TestingHUD.h"
#include "TestingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATestingGameMode::ATestingGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingHUD::StaticClass();
}
