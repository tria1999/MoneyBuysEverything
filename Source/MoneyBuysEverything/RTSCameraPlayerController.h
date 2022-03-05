// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AbilitySystemInterface.h"
#include "RTSCameraPlayerController.generated.h"

class AMobaUnit;
class AController;

UCLASS()
class ARTSCameraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARTSCameraPlayerController();

	UPROPERTY(EditAnywhere, Category = "Main Character")
	AMobaUnit* MainCharacter;


	UFUNCTION()
	void OpenInGameMenu();
	UFUNCTION()
	void MoveToMouseCursor();
	UFUNCTION()
	void OnSetDestinationPressed();
	UFUNCTION()
	void OnSetDestinationReleased();
	UFUNCTION()
	void OnStop();
	UFUNCTION()
	void OnAttackMove();

	virtual void SetupInputComponent() override;

protected:
	UPROPERTY()
	uint32 bMoveToMouseCursor : 1;
	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void PlayerTick(float DeltaSeconds) override;
	
};
