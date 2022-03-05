// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"


bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if(!Success) return false;
    if(HostBtn==nullptr) return false;
    HostBtn->OnClicked.AddDynamic(this,&UMainMenu::HostServer);
    if(JoinBtn==nullptr) return false;
    JoinBtn->OnClicked.AddDynamic(this,&UMainMenu::OpenJoinMenu);
    if (QuitBtn == nullptr) return false;
    QuitBtn->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
    if(CancelBtn==nullptr) return false;
    CancelBtn->OnClicked.AddDynamic(this,&UMainMenu::ToMainMenu);
    if(JoinGameBtn==nullptr) return false;
    JoinGameBtn->OnClicked.AddDynamic(this,&UMainMenu::JoinServer);

    
    return true;
}



void UMainMenu::HostServer()
{
    if(MenuInterface)
    {
        MenuInterface->Host();
    }
}

void UMainMenu::OpenJoinMenu()
{
    if(MenuSwitcher==nullptr) return;
    if(JoinMenu==nullptr) return;
    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::ToMainMenu()
{
    if(MenuSwitcher==nullptr) return;
    if(MainMenu==nullptr) return; 
    MenuSwitcher->SetActiveWidget(MainMenu);
}
void UMainMenu::JoinServer()
{
    if(MenuInterface)
    {
        if(IPAddressField==nullptr) return;
        const FString IPAddress = IPAddressField->GetText().ToString();
        MenuInterface->Join(IPAddress);
    }
}

void UMainMenu::QuitGame()
{
    if (MenuInterface)
    {
        MenuInterface->QuitGame();
    }
}