// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaUnit.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"

#include "../../MoneyBuysEverything.h"


#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Math/Vector.h"





// Sets default values
AMobaUnit::AMobaUnit()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //init AttackMove
    ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
    //ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));

    

}




/*TSubclassOf<FGameplayAbilitySpec> AMobaUnit::GetAbilityByName(FName Name, TArray<TSubclassOf<FGameplayAbilitySpec>> AbilityArray)
{

    for (TSubclassOf<FGameplayAbilitySpec>& Ability : AbilityArray)
    {
        
    }

    return nullptr;
}*/

// Called when the game starts or when spawned
void AMobaUnit::BeginPlay()
{
	Super::BeginPlay();

    ActorsToIgnore.Add(this);

   // UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(this->GetCharacterMovement());
    //if(Attributes)
     //   MovementComponent->MaxWalkSpeed = Attributes->GetBaseMoveSpeed();

    Attributes->SetAtkRange(600.f);
    bIsReceivingCommands = true;
    bCanAttack = true;
    bInAttack = false;
    bIsAttackMoving = false;
    bIsAttacking = false;
    ClearCommands();
   
}

// Called every frame
void AMobaUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (bIsAttacking)
    {
        if (TargetSelectable)
            MoveToAttack(TargetSelectable);
    }
    else if (bIsAttackMoving)
    {
        AttackMoveCheck();
    }
       

}


void AMobaUnit::MoveToLocation(FVector Location)
{
    UAIBlueprintHelperLibrary::SimpleMoveToLocation(this->GetController(), Location);
    /*if (this->GetActorLocation() != Location)
        
    else
        ClearCommands();*/
}

void AMobaUnit::AttackMoveCheck()
{
    //optimize init
    bool EnemyInRange = false;
    TArray<AActor*> OutActors;
    EnemyInRange = UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
        this->GetActorLocation(), Attributes->GetAtkRange(),
        ObjectTypes,
        nullptr, ActorsToIgnore, OutActors);

    if (EnemyInRange)
    {
        UE_LOG(LogTemp, Warning, TEXT("Enemy In %f Range"), Attributes->GetAtkRange());
        AActor* NearestActor = nullptr;
        float MinDist = Attributes->GetAtkRange();
        for (AActor* NearbyActor : OutActors)
        {
            if (this->GetDistanceTo(NearbyActor) < MinDist)
            {
                NearestActor = NearbyActor;
                MinDist = this->GetDistanceTo(NearbyActor);
            }
        }
        if (NearestActor != nullptr)
            if (AMobaSelectable* NearestTarget = Cast<AMobaSelectable>(NearestActor))
                if (this->GetGenericTeamId() != NearestTarget->GetGenericTeamId())
                {
                    bIsAttackMoving = false;
                    this->CommandAttack(NearestTarget);
                }

    }
    //else MoveToLocation(TargetLocation);
}

void AMobaUnit::MoveToAttack(AMobaSelectable* Target)
{
    if (Target)
    {
        if (this->GetDistanceTo(Target) > Attributes->GetAtkRange()+200)
        {
            
            UAIBlueprintHelperLibrary::SimpleMoveToActor(this->GetController(), Target);
        }
        else
        {
            Face();
            AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EMobaAbilityInputID::CLICK));//ATTACK STARTS HERE
            
            //AbilitySystemComponent->TryAct("BasicAttack.Instant", true)
                //PerformAttack();
        }
    }
}

void AMobaUnit::RecieveCommand(int32 Command, FHitResult Hit)
{
    if (bIsReceivingCommands)
    {
        ClearCommands();
        switch (Command)
        {
        case 0:
            CommandMoveOrAttack(Hit);
            break;
        case 1:
            //ClearCommands();
            break;
        case 2:
            CommandAttackMove(Hit);
            break;
        }
    }
}

//this is kind of a mess
void AMobaUnit::CommandMoveOrAttack(FHitResult Hit)
{
    if (AActor* ActorHit = Hit.GetActor())
    {
        if (AMobaSelectable* TargetHit = Cast<AMobaSelectable>(ActorHit))
        {
            
            if (this->GetGenericTeamId() != TargetHit->GetGenericTeamId())// We hit an enemy, move to attack
            {
                bIsAttackMoving = false;
                this->CommandAttack(TargetHit);
            }
            else
                this->MoveToLocation(Hit.Location);
        }
        else
            this->MoveToLocation(Hit.Location);
    }
    else
        this->MoveToLocation(Hit.Location);
}

void AMobaUnit::CommandAttack(AMobaSelectable* Enemy)
{
    
    bIsAttacking = true;
    TargetSelectable = Enemy;
    /*
    if (bIsReceivingCommands)
    {
        //ClearCommands();
        
    }*/
}

void AMobaUnit::CommandAttackMove(FHitResult Hit)
{
    if (bIsReceivingCommands)
    {
        ClearCommands();
        bIsAttackMoving = true;
        CommandMoveOrAttack(Hit);
        
    }
}

void AMobaUnit::ClearCommands()
{
    bIsMoving = false;
    bIsAttacking = false;
    bIsAttackMoving = false;
    UAIBlueprintHelperLibrary::SimpleMoveToActor
    (this->GetController(), this);
}


void AMobaUnit::Face()
{
    if (TargetSelectable)
    {
        FVector DashVector = UKismetMathLibrary::GetDirectionUnitVector(this->GetActorLocation(), TargetSelectable->GetActorLocation());
        FVector DashVectorCleaned = FVector(DashVector.X, DashVector.Y, this->GetActorLocation().Z);
        FRotator FaceRotation = FVector(DashVectorCleaned).Rotation();
        FRotator FaceRotationCleaned = FRotator(0.f, FaceRotation.Yaw, 0.f);
        this->SetActorRotation(FaceRotationCleaned);
    }
}

