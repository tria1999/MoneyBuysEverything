// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaTestHeroAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <MoneyBuysEverything/Selectable/Unit/Mercenaries/Mercenary.h>

UMobaTestHeroAnimInstance::UMobaTestHeroAnimInstance()
{
    Speed = 0.f;
   // bIsDashing = false;
}

void UMobaTestHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    AActor* OwningActor = GetOwningActor();

    if(OwningActor)
    {
        Speed = OwningActor->GetVelocity().Size();
        AMercenary* OwningCharacter = Cast<AMercenary>(OwningActor);
        if (OwningCharacter)
        {
            //bIsDashing = OwningCharacter->bIsDashing;
           // bInAttack = OwningCharacter->bInAttack;
            //bInUlt = OwningCharacter->bIsInUltAnim;
        }

    }
    else
    {UE_LOG(LogTemp,Warning,TEXT("Animation fault"));}
}
