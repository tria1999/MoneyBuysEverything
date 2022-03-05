// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MobaAttributeSet.generated.h"

// Uses macros from AttributeSet.h 
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
/**
 * 
 */
UCLASS()
class MONEYBUYSEVERYTHING_API UMobaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public: 

	UMobaAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_BaseHP)
	FGameplayAttributeData BaseHP;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, BaseHP);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxHP)
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, MaxHP);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_CurrentHP)
	FGameplayAttributeData CurrentHP;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, CurrentHP);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_BaseResource)
	FGameplayAttributeData BaseResource;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, BaseResource);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MaxResource)
	FGameplayAttributeData MaxResource;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, MaxResource);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_CurrentResource)
	FGameplayAttributeData CurrentResource;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, CurrentResource);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, Level);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_AtkRange)
	FGameplayAttributeData AtkRange;// = 125.f
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, AtkRange);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_BaseAtkSpeed)
	FGameplayAttributeData BaseAtkSpeed; //= 0.7f
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, BaseAtkSpeed);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_AtkSpeed)
	FGameplayAttributeData AtkSpeed;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, AtkSpeed);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_BaseMoveSpeed)
	FGameplayAttributeData BaseMoveSpeed;// = 350.0f;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, BaseMoveSpeed);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MoveSpeed)
	FGameplayAttributeData MoveSpeed;// = 350.0f;
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, MoveSpeed);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_AtkDamage)
	FGameplayAttributeData AtkDamage;//= 80.f
	ATTRIBUTE_ACCESSORS(UMobaAttributeSet, AtkDamage);



	UFUNCTION()
	virtual void OnRep_BaseHP(const FGameplayAttributeData& OldBaseHP);
	UFUNCTION()
	virtual void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP);
	UFUNCTION()
	virtual void OnRep_CurrentHP(const FGameplayAttributeData& OldCurrentHP);
	UFUNCTION()
	virtual void OnRep_BaseResource(const FGameplayAttributeData& OldBaseResource);
	UFUNCTION()
	virtual void OnRep_MaxResource(const FGameplayAttributeData& OldMaxResource);
	UFUNCTION()
	virtual void OnRep_CurrentResource(const FGameplayAttributeData& OldCurrentResource);
	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldLevel);
	UFUNCTION()
	virtual void OnRep_AtkRange(const FGameplayAttributeData& OldAtkRange);
	UFUNCTION()
	virtual void OnRep_BaseAtkSpeed(const FGameplayAttributeData& OldBaseAtkSpeed);
	UFUNCTION()
	virtual void OnRep_AtkSpeed(const FGameplayAttributeData& OldAtkSpeed);
	UFUNCTION()
	virtual void OnRep_BaseMoveSpeed(const FGameplayAttributeData& OldBaseMoveSpeed);
	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldMoveSpeed);
	UFUNCTION()
	virtual void OnRep_AtkDamage(const FGameplayAttributeData& OldAtkDamage);

	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);


	
};
