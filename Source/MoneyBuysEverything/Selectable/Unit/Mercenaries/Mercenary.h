// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MobaUnit.h"
#include "Mercenary.generated.h"

/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API AMercenary : public AMobaUnit
{
	GENERATED_BODY()
public:
	AMercenary();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
	UMobaAttributeSet* MercenaryAttributes;

	virtual void BeginPlay() override;
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

};
