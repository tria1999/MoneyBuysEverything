// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTSCameraPlayerController.h"
#include "GenericTeamAgentInterface.h"

#include "RTSCameraModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARTSCameraModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:

	UFUNCTION()
	void HandleGameStart();
	UFUNCTION()
	void HandleGameOver(FGenericTeamId Team);
	UFUNCTION()
	void ReturnToMenu();

	UPROPERTY()
	FTimerHandle ReturnToMenuTimerHandle;

public:
	ARTSCameraModeBase();
	UFUNCTION(BlueprintCallable)
	void ActorDied(AActor* DeadActor);

protected:

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(FGenericTeamId Team);

};
