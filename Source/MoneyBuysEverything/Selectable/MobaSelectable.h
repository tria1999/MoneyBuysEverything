 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "..\Component\MobaAbilitySystemComponent.h"
#include "..\Component\MobaAttributeSet.h"
#include "GenericTeamAgentInterface.h"
#include "..\Actor\ProjectileBase.h"
#include "MobaSelectable.generated.h"


UCLASS()
class MONEYBUYSEVERYTHING_API AMobaSelectable : public ACharacter, public IGenericTeamAgentInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMobaSelectable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
*/

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;


//GAS
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
		UMobaAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GAS")
		UMobaAttributeSet* Attributes;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "GAS")
		virtual void InitializeAttributes();

	//UFUNCTION(BlueprintCallable, Category = "GAS")
	//void AddEffect(TSubclassOf<UGameplayEffect> Effect);

	virtual void GiveAbilities();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//TSubclassOf<class FGameplayAbilitySpec> GetAbilityByName(FName Name, TArray<TSubclassOf<class FGameplayAbilitySpec>> AbilityArray);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TArray<TSubclassOf<class UMobaGameplayAbility>> DefaultAbilities;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
		TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
		TSubclassOf<class UMobaGameplayAbility> BasicAttack;

	UPROPERTY()
		int32 bAbilitiesInitialized;
	
	
	UFUNCTION(BlueprintCallable)
	virtual float GetBaseHP() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetMaxHP() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetCurrentHP() const;
	UFUNCTION(BlueprintCallable)
	virtual	float GetBaseAtkSpeed() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetLevel() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetAtkSpeed() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetBaseMoveSpeed() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetMoveSpeed() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetAtkDamage() const;
	UFUNCTION(BlueprintCallable)
	virtual float GetAtkRange() const;
	
	
	/**
	 * Called when character takes damage, which may have killed them
	 *
	 * @param DamageAmount Amount of damage that was done, not clamped based on current health
	 * @param HitInfo The hit info that generated this damage
	 * @param DamageTags The gameplay tags of the event that did the damage
	 * @param InstigatorCharacter The character that initiated this damage
	 * @param DamageCauser The actual actor that did the damage, might be a weapon or projectile
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AMobaSelectable* InstigatorCharacter, AActor* DamageCauser);

	/**
	 * Called when health is changed, either from healing or from being damaged
	 * For damage this is called in addition to OnDamaged/OnKilled
	 *
	 * @param DeltaValue Change in health value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnHPChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * Called when mana is changed, either from healing or from being used as a cost
	 *
	 * @param DeltaValue Change in mana value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnResourceChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * Called when movement speed is changed
	 *
	 * @param DeltaValue Change in move speed
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void OnMoveSpeedChanged(float DeltaValue,      
		
		
		const struct FGameplayTagContainer& EventTags);

	// Called from RPGAttributeSet, these call BP events above
	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AMobaSelectable* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHPChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleResourceChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	// Friended to allow access to handle functions above
	friend UMobaAttributeSet;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	FGenericTeamId Team;
	UFUNCTION(BlueprintCallable)
	virtual FGenericTeamId GetGenericTeamId() const override;
	 
};
