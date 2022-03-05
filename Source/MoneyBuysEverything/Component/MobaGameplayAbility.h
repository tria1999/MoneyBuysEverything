// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Abilities/GameplayAbility.h>
#include "../MoneyBuysEverything.h"
#include "MobaGameplayAbility.generated.h"


/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API UMobaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	UMobaGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	FName AbilityName;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EMobaAbilityInputID AbilityInputID = EMobaAbilityInputID::NONE;
	
};
