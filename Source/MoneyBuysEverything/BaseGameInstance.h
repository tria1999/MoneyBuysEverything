// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Menu/MenuInterface.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API UBaseGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UBaseGameInstance(const FObjectInitializer & ObjectInitializer);

	virtual void Init();

	UFUNCTION(BlueprintCallable)
	void LoadMenu();

	UFUNCTION(BlueprintCallable)
	void LoadInGameMenu();

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);
	
	UFUNCTION(Exec)
	virtual void LoadMainMenu() override;

	UFUNCTION(Exec)
	virtual void QuitGame() override;

private:
	TSubclassOf<class UUserWidget> MenuClass;
	TSubclassOf<class UUserWidget> InGameMenuClass;

	
	class UMainMenu* Menu;
	
};