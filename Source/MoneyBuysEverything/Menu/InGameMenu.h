// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "InGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API UInGameMenu : public UMenuWidget
{
	GENERATED_BODY()

// public:

// 	UFUNCTION()
// 	void EscPressed();
protected:
	UFUNCTION()
	virtual bool Initialize() override;

private:

	UPROPERTY(meta=(BindWidget))
	class UButton* CloseInGameMenuBtn;

	UPROPERTY(meta=(BindWidget))
	class UButton* QuitToMainMenuBtn;

	UPROPERTY()
	bool MenuOpen = false;


	// UFUNCTION()
	// void OpenInGameMenu();

	UFUNCTION()
	void QuitToMainMenu();

	UFUNCTION()
	void CloseInGameMenu();
};
