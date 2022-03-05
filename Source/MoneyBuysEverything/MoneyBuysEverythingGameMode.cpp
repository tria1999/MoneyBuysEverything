// Copyright Epic Games, Inc. All Rights Reserved.

#include "MoneyBuysEverythingGameMode.h"
#include "MoneyBuysEverythingPlayerController.h"
#include "MoneyBuysEverythingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMoneyBuysEverythingGameMode::AMoneyBuysEverythingGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMoneyBuysEverythingPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}