// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"
#include "Engine/Engine.h"
 
bool UInGameMenu::Initialize()
{
    bool Success = Super::Initialize();
    if(!Success) return false;
    if(CloseInGameMenuBtn==nullptr) return false;
    CloseInGameMenuBtn->OnClicked.AddDynamic(this,&UInGameMenu::CloseInGameMenu);
    if(QuitToMainMenuBtn==nullptr) return false;
    QuitToMainMenuBtn->OnClicked.AddDynamic(this,&UInGameMenu::QuitToMainMenu);
    
    return true;
}


// void UInGameMenu::EscPressed()
// {
//     if(!MenuOpen)
//         this->OpenInGameMenu();
//     else
//         this->CloseInGameMenu();
// }

// void UInGameMenu::OpenInGameMenu()
// {
//     MenuOpen=true;
//     this->AddToViewport();
//     this->bIsFocusable = true;

// }

void UInGameMenu::CloseInGameMenu()
{
    this->RemoveFromViewport();
    this->bIsFocusable = false;
    
    MenuOpen=false;

}

void UInGameMenu::QuitToMainMenu()
{
    if (MenuInterface)
    {
        MenuInterface->LoadMainMenu();
    }
}