// Fill out your copyright notice in the Description page of Project Settings.

#include "RTSCameraPlayerController.h"
#include "MoneyBuysEverything.h"
#include "CameraPawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "Selectable/Unit/MobaUnit.h"

#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Menu/InGameMenu.h"

ARTSCameraPlayerController::ARTSCameraPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;	
}

void ARTSCameraPlayerController::BeginPlay()
{
	Super::BeginPlay();	

	
}

void ARTSCameraPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);	

	// keep updating the destination every tick while desired
	
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}


void ARTSCameraPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	
	//General Commands
	InputComponent->BindAction("OpenInGameMenu", IE_Pressed, this, &ARTSCameraPlayerController::OpenInGameMenu);
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARTSCameraPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ARTSCameraPlayerController::OnSetDestinationReleased);
	InputComponent->BindAction("Stop", IE_Pressed, this, &ARTSCameraPlayerController::OnStop);
	InputComponent->BindAction("AttackMove", IE_Pressed, this, &ARTSCameraPlayerController::OnAttackMove);

	/*
	//Mercenary Commands 
	InputComponent->BindAction("Q", IE_Pressed, this, &ARTSCameraPlayerController::OnQ);
	InputComponent->BindAction("W", IE_Pressed, this, &ARTSCameraPlayerController::OnW);
	InputComponent->BindAction("E", IE_Pressed, this, &ARTSCameraPlayerController::OnE);
	InputComponent->BindAction("R", IE_Pressed, this, &ARTSCameraPlayerController::OnR);
	
	const FGameplayAbilityInputBinds Binds("NONE", "CLICK", "EGASAbilityInputID",
		static_cast<int32>(EMobaAbilityInputID::NONE), static_cast<int32>(EMobaAbilityInputID::CLICK));

	MainCharacter->GetAbilitySystemComponent()->BindAbilityActivationToInputComponent(InputComponent, Binds);
	*/
	/*
	* CLICK = 0;
	* STOP = 1;
	* ATTACK_MOVE = 2;
	* Q = 21
	* W = 22
	* E = 23
	* R = 24
	*/

}

void ARTSCameraPlayerController::OpenInGameMenu()
{
	//open in game menu
}

// Function that sends move command while the mouse is pressed

void ARTSCameraPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if(AMobaUnit* MyHero = Cast<AMobaUnit>(MainCharacter))
	{
		if (Hit.bBlockingHit)
		{
			MyHero->RecieveCommand(0, Hit);
		}
	}
}

void ARTSCameraPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ARTSCameraPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ARTSCameraPlayerController::OnStop()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if(AMobaUnit* MyHero = Cast<AMobaUnit>(MainCharacter))
	{
		MyHero->RecieveCommand(1, Hit);
		bMoveToMouseCursor = false;
	}
}

void ARTSCameraPlayerController::OnAttackMove()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (AMobaUnit* MyHero = Cast<AMobaUnit>(MainCharacter))
	{
		MyHero->RecieveCommand(2, Hit);
	}
}
