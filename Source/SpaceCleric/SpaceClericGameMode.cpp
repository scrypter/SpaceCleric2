// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SpaceClericGameMode.h"
#include "SCClientController.h"
#include "SCServerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpaceClericGameMode::ASpaceClericGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASCClientController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}