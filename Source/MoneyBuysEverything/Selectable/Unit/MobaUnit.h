// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\MobaSelectable.h"
#include <GameplayEffectTypes.h>
#include "UObject/ScriptInterface.h"
#include "MobaUnit.generated.h"

/**
 * 
 */
class UCapsuleComponent;

UCLASS()
class MONEYBUYSEVERYTHING_API AMobaUnit : public AMobaSelectable
{	
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMobaUnit();
	
	


	//commands
	UFUNCTION()
	void RecieveCommand(int32 Command, FHitResult Hit);
	UFUNCTION()
	void CommandMoveOrAttack(FHitResult Hit);
	UFUNCTION()
	void CommandAttack(AMobaSelectable* Enemy);
	UFUNCTION()
	void CommandAttackMove(FHitResult Hit);

	//actions
	UFUNCTION()
	void ClearCommands();
	UFUNCTION()
	void MoveToAttack(AMobaSelectable* Target);


	
	UFUNCTION()
	void Face();


	
	//current command
	UPROPERTY()
	bool bIsMoving;
	UPROPERTY()
	bool bIsAttackMoving;
	UPROPERTY()
	FVector TargetLocation;
	UPROPERTY()
	bool bIsAttacking;
	
	UPROPERTY(BlueprintReadOnly)
	AMobaSelectable* TargetSelectable;
	

	UPROPERTY()
	bool bInAttack;
	UPROPERTY()
	bool bIsReceivingCommands;

	//allowed actions
	UPROPERTY()
	bool bCanAttack;
	//timer handles


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//properties for optimization
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;




	void MoveToLocation(FVector Location);
	void AttackMoveCheck();
	

};
