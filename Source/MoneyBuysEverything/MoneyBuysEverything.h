// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMobaAbilityInputID : uint8
{
	NONE,
	CLICK, 
	STOP
	/*
	* CLICK = 0;
	* STOP = 1;
	* ATTACK_MOVE = 2;
	* Q = 21
	* W = 22
	* E = 23
	* R = 24
	*/
};

DECLARE_LOG_CATEGORY_EXTERN(LogMoneyBuysEverything, Log, All);