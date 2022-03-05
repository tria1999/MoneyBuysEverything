// Fill out your copyright notice in the Description page of Project Settings.


#include "Mercenary.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/CapsuleComponent.h"
#include "../../../Component/MobaGameplayAbility.h"
#include "../../../Component/MobaAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Math/Vector.h"
#include "TimerManager.h"


AMercenary::AMercenary()
{
    
    MercenaryAttributes = CreateDefaultSubobject<UMobaAttributeSet>(TEXT("Mercenary Attributes"));
    
    
}

void AMercenary::BeginPlay()
{
    Super::BeginPlay();
    UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(this->GetCharacterMovement());
    if (MercenaryAttributes)
    {
        MercenaryAttributes->SetBaseMoveSpeed(333.f);
        MovementComponent->MaxWalkSpeed = MercenaryAttributes->GetBaseMoveSpeed();

    }
    else
        UE_LOG(LogTemp, Warning, TEXT("cant init attributs "));
}
void AMercenary::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(this->GetCharacterMovement());
    if (MercenaryAttributes)
    {
        MercenaryAttributes->SetBaseMoveSpeed(333.f);
        MovementComponent->MaxWalkSpeed = MercenaryAttributes->GetBaseMoveSpeed();

    }

}


