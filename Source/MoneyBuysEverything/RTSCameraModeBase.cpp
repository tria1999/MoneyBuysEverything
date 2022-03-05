// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCameraModeBase.h"
#include "RTSCameraPlayerController.h"
#include "BaseGameInstance.h"
#include "CameraPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Selectable/Building/Headquarters.h"


ARTSCameraModeBase::ARTSCameraModeBase()
{
	PlayerControllerClass = ARTSCameraPlayerController::StaticClass();
	DefaultPawnClass = ACameraPawn::StaticClass();
}

void ARTSCameraModeBase::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

}

void ARTSCameraModeBase::ActorDied(AActor* DeadActor)
{
    /*if (DeadActor == PlayerTank)
    {
        PlayerTank->HandleDestruction();
        HandleGameOver(false);

        if (PlayerControllerRef)
        {
            PlayerControllerRef->SetPlayerEnabledState(false);
        }
    }
    else */
    if (AMobaSelectable* DestroyedStructure = Cast<AMobaSelectable>(DeadActor))
    {
        

        if (AHeadquarters* DestroyedHQ = Cast<AHeadquarters>(DeadActor))
        {
            if (DestroyedHQ == nullptr) return;
            DestroyedHQ->HandleDestruction();
            HandleGameOver(DestroyedHQ->GetGenericTeamId());
        }
    }
}

void ARTSCameraModeBase::HandleGameStart()
{
    /*for (TActorIterator<AMercenary> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        if(ActorItr->GetName().Equals(TEXT("BP_Mercenary_2"), ESearchCase::CaseSensitive))
        {
            MainCharacter = Cast<AMercenary>(*ActorItr);
            return;
        }
    }*/
}

void ARTSCameraModeBase::HandleGameOver(FGenericTeamId Team)
{
    //UGameplayStatics::SetGamePaused(GetWorld(),true);
    GameOver(Team);
    GetWorld()->GetTimerManager().SetTimer(ReturnToMenuTimerHandle,
        this, &ARTSCameraModeBase::ReturnToMenu, 5.f, false);
}


void ARTSCameraModeBase::ReturnToMenu()
{
    UE_LOG(LogTemp, Warning, TEXT("In ReturnToMenu"));
    UBaseGameInstance* GameInstance = Cast<UBaseGameInstance>(GetWorld()->GetGameInstance());
    if(GameInstance!=nullptr)
    UE_LOG(LogTemp, Warning, TEXT("Load Menu"));
        GameInstance->LoadMainMenu();

}
