// Copyright Epic Games, Inc. All Rights Reserved.

#include "FroggerGameMode.h"
#include "FroggerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFroggerGameMode::AFroggerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
