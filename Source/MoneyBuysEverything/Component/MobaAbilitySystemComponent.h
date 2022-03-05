// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MobaAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API UMobaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	

	/** Returns the default level used for ability activations, derived from the character */
	int32 GetDefaultAbilityLevel() const;


};
