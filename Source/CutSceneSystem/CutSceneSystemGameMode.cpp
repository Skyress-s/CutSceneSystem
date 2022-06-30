// Copyright Epic Games, Inc. All Rights Reserved.

#include "CutSceneSystemGameMode.h"
#include "CutSceneSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACutSceneSystemGameMode::ACutSceneSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
