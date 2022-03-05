// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"

#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void Setup();
	
	void SetMenuInterface(IMenuInterface* MyMenuInterface);
	
protected:
	virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

	IMenuInterface* MenuInterface;

};
