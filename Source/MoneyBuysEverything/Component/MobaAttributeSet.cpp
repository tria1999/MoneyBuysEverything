// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "MobaAbilitySystemComponent.h"
#include "..\Selectable\Unit\MobaUnit.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"

UMobaAttributeSet::UMobaAttributeSet(){}

void UMobaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetMaxHPAttribute())
	{
		AdjustAttributeForMaxChange(CurrentHP, MaxHP, NewValue, GetCurrentHPAttribute());
	}
	else if (Attribute == GetMaxResourceAttribute())
	{
		AdjustAttributeForMaxChange(CurrentResource, MaxResource, NewValue, GetCurrentResourceAttribute());
	}
	
}
void UMobaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}
	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	AController* TargetController = nullptr;
	AMobaSelectable* TargetCharacter = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		TargetCharacter = Cast<AMobaSelectable>(TargetActor);
	}

	if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		if (AMobaUnit* Unit = Cast<AMobaUnit>(TargetCharacter))
		{
			// Call for all movespeed changes
			Unit->HandleMoveSpeedChanged(DeltaValue, SourceTags);
		}
	}


	if (Data.EvaluatedData.Attribute == GetAtkDamageAttribute())
	{
		// Get the Source actor
		AActor* SourceActor = nullptr;
		AController* SourceController = nullptr;
		AMobaSelectable* SourceCharacter = nullptr;
		if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
		{
			SourceActor = Source->AbilityActorInfo->AvatarActor.Get();
			SourceController = Source->AbilityActorInfo->PlayerController.Get();
			if (SourceController == nullptr && SourceActor != nullptr)
			{
				if (APawn* Pawn = Cast<APawn>(SourceActor))
				{
					SourceController = Pawn->GetController();
				}
			}

			// Use the controller to find the source pawn
			if (SourceController)
			{
				SourceCharacter = Cast<AMobaSelectable>(SourceController->GetPawn());
			}
			else
			{
				SourceCharacter = Cast<AMobaSelectable>(SourceActor);
			}

			// Set the causer actor based on context if it's set
			if (Context.GetEffectCauser())
			{
				SourceActor = Context.GetEffectCauser();
			}
		}

		// Try to extract a hit result
		FHitResult HitResult;
		if (Context.GetHitResult())
		{
			HitResult = *Context.GetHitResult();
		}

		// Store a local copy of the amount of damage done and clear the damage attribute
		const float LocalDamageDone = GetAtkDamage();
		SetAtkDamage(0.f);

		if (LocalDamageDone > 0)
		{
			// Apply the health change and then clamp it
			const float OldHP = GetCurrentHP();
			SetCurrentHP(FMath::Clamp(OldHP - LocalDamageDone, 0.0f, GetMaxHP()));

			if (TargetCharacter)
			{
				// This is proper damage
				TargetCharacter->HandleDamage(LocalDamageDone, HitResult, SourceTags, SourceCharacter, SourceActor);

				// Call for all health changes
				TargetCharacter->HandleHPChanged(-LocalDamageDone, SourceTags);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentHPAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetCurrentHP(FMath::Clamp(GetCurrentHP(), 0.0f, GetMaxHP()));

		if (TargetCharacter)
		{
			// Call for all health changes
			TargetCharacter->HandleHPChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentResourceAttribute())
	{
		// Clamp Resource
		SetCurrentResource(FMath::Clamp(GetCurrentResource(), 0.0f, GetMaxResource()));

		if (TargetCharacter)
		{
			// Call for all Resource changes
			TargetCharacter->HandleResourceChanged(DeltaValue, SourceTags);
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMoveSpeedAttribute())
	{
		if (TargetCharacter)
		{
			// Call for all movespeed changes
			TargetCharacter->HandleMoveSpeedChanged(DeltaValue, SourceTags);
		}
	}
}


void UMobaAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, BaseHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, CurrentHP, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, BaseResource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, MaxResource, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, CurrentResource, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, Level, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, AtkRange, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, BaseAtkSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, AtkSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, BaseMoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMobaAttributeSet, AtkDamage, COND_None, REPNOTIFY_Always);
}



void UMobaAttributeSet::UMobaAttributeSet::OnRep_BaseHP(const FGameplayAttributeData& OldBaseHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, BaseHP, OldBaseHP);
}
void UMobaAttributeSet::UMobaAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, MaxHP, OldMaxHP);
}
void UMobaAttributeSet::UMobaAttributeSet::OnRep_CurrentHP(const FGameplayAttributeData& OldCurrentHP)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, CurrentHP, OldCurrentHP);
}

void UMobaAttributeSet::UMobaAttributeSet::OnRep_BaseResource(const FGameplayAttributeData& OldBaseResource)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, BaseResource, OldBaseResource);
}
void UMobaAttributeSet::UMobaAttributeSet::OnRep_MaxResource(const FGameplayAttributeData& OldMaxResource)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, MaxResource, OldMaxResource);
}
void UMobaAttributeSet::UMobaAttributeSet::OnRep_CurrentResource(const FGameplayAttributeData& OldCurrentResource)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, CurrentResource, OldCurrentResource);
}


void UMobaAttributeSet::UMobaAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, Level, OldLevel);
}

 void UMobaAttributeSet::OnRep_AtkRange(const FGameplayAttributeData& OldAtkRange)
 {
	 GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, AtkRange, OldAtkRange);
 }

 void UMobaAttributeSet::OnRep_BaseAtkSpeed(const FGameplayAttributeData& OldBaseAtkSpeed)
 {
	 GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, BaseAtkSpeed, OldBaseAtkSpeed);
 }

 void UMobaAttributeSet::OnRep_AtkSpeed(const FGameplayAttributeData& OldAtkSpeed)
 {
	 GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, AtkSpeed, OldAtkSpeed);
 }

 void UMobaAttributeSet::OnRep_BaseMoveSpeed(const FGameplayAttributeData& OldBaseMoveSpeed)
 {
	 GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, BaseMoveSpeed, OldBaseMoveSpeed);
 }

 void UMobaAttributeSet::OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed)
 {
	 GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, MoveSpeed, OldMoveSpeed);
 }

 void UMobaAttributeSet::OnRep_AtkDamage(const FGameplayAttributeData& OldAtkDamage)
 {
	 GAMEPLAYATTRIBUTE_REPNOTIFY(UMobaAttributeSet, AtkDamage, OldAtkDamage);
 }

 void UMobaAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
 {
	 UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	 const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	 if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	 {
		 // Change current value to add to the current the change to max %
		 const float CurrentValue = AffectedAttribute.GetCurrentValue();
		 float NewDelta = (CurrentMaxValue > 0.f) ? CurrentValue + NewMaxValue - CurrentMaxValue: NewMaxValue;

		 AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	 }
 }

