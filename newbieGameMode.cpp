// Copyright Epic Games, Inc. All Rights Reserved.

#include "newbieGameMode.h"
#include "newbieCharacter.h"
#include "NewbiePlayerController.h"
#include "UObject/ConstructorHelpers.h"

AnewbieGameMode::AnewbieGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	PlayerControllerClass = ANewbiePlayerController::StaticClass();
}
