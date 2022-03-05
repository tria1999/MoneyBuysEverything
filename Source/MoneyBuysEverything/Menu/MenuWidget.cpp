// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::SetMenuInterface(IMenuInterface* MyMenuInterface)
{
    this->MenuInterface = MyMenuInterface;
}

void UMenuWidget::Setup()
{
    this->AddToViewport();
    
    this->bIsFocusable = true;

    // UWorld* World = GetWorld();
    // if(World==nullptr) return;
    // APlayerController* PlayerController = World->GetFirstPlayerController();
    // if(PlayerController==nullptr) return;

    // FInputModeUIOnly InputModeData;
    // InputModeData.SetWidgetToFocus(this->TakeWidget());
    // InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

    // PlayerController->SetInputMode(InputModeData);
    
    // PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    this->bIsFocusable = false;

    this->RemoveFromViewport();
    

    // APlayerController* PlayerController = InWorld->GetFirstPlayerController();
    // if(PlayerController==nullptr) return;

    // FInputModeGameAndUI InputModeData;

    // PlayerController->SetInputMode(InputModeData);
    
    // PlayerController->bShowMouseCursor = true;

}