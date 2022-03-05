// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MobaSelectable.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "Building.generated.h"

/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API ABuilding : public AMobaSelectable
{
	GENERATED_BODY()
		
public:
	ABuilding();

	void Destroyed();
	UFUNCTION(BlueprintCallable)
	virtual void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
