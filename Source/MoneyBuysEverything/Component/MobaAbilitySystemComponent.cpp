// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAbilitySystemComponent.h"
#include "..\Selectable\Unit\MobaUnit.h"
#include "AbilitySystemGlobals.h"

int32 UMobaAbilitySystemComponent::GetDefaultAbilityLevel() const
{
	AMobaUnit* OwningCharacter = Cast<AMobaUnit>(GetOwnerActor());

	if (OwningCharacter)
	{
		return OwningCharacter->GetLevel();
	}
	return 1;
}