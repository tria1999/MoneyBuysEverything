// Fill out your copyright notice in the Description page of Project Settings.


#include "MobaSelectable.h"
#include "../Component/MobaGameplayAbility.h"
#include "../Component/MobaAttributeSet.h"
#include "AbilitySystemGlobals.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMobaSelectable::AMobaSelectable()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    AbilitySystemComponent = CreateDefaultSubobject<UMobaAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
    AbilitySystemComponent->SetIsReplicated(true);
    AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

    Attributes = CreateDefaultSubobject<UMobaAttributeSet>(TEXT("Attributes"));

    bAbilitiesInitialized = false;

    BaseMesh = this->GetMesh();

    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Basic Attack Projectile Spawn Point"));
    ProjectileSpawnPoint->SetupAttachment(BaseMesh);
}
class UAbilitySystemComponent* AMobaSelectable::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void AMobaSelectable::InitializeAttributes()
{
    if (AbilitySystemComponent && DefaultAttributeEffect)
    {
        FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
        EffectContext.AddSourceObject(this);
        FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
        if (SpecHandle.IsValid())
        {
            FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
        }
    }
}

void AMobaSelectable::GiveAbilities()
{
    if (HasAuthority() && AbilitySystemComponent)

    {
        for (TSubclassOf<UMobaGameplayAbility>& StartingAbility : DefaultAbilities)
        {
            AbilitySystemComponent->GiveAbility(
                FGameplayAbilitySpec(StartingAbility, 1, static_cast<int32>(StartingAbility.GetDefaultObject()->AbilityInputID), this));
        }
    }


    bAbilitiesInitialized = true;
}

void AMobaSelectable::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);

    //Server GAS init
    AbilitySystemComponent->InitAbilityActorInfo(this, this);

    InitializeAttributes();
    GiveAbilities();
    //it runs
}

void AMobaSelectable::OnRep_PlayerState()
{
    Super::OnRep_PlayerState();

    AbilitySystemComponent->InitAbilityActorInfo(this, this);
    InitializeAttributes();

    if (AbilitySystemComponent && InputComponent)
    {
        const FGameplayAbilityInputBinds Binds("NONE", "CLICK", "EGASAbilityInputID", static_cast<int32>(EMobaAbilityInputID::NONE), static_cast<int32>(EMobaAbilityInputID::CLICK));
        AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, Binds);
    }
}

// Called when the game starts or when spawned
void AMobaSelectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMobaSelectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*Called to bind functionality to input
void AMobaSelectable::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
*/
FGenericTeamId AMobaSelectable::GetGenericTeamId() const
{
	return Team;
}

void AMobaSelectable::HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AMobaSelectable* InstigatorPawn, AActor* DamageCauser)
{
    OnDamaged(DamageAmount, HitInfo, DamageTags, InstigatorPawn, DamageCauser);
}

void AMobaSelectable::HandleHPChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
    // We only call the BP callback if this is not the initial ability setup
    if (bAbilitiesInitialized)
    {
        OnHPChanged(DeltaValue, EventTags);
        UE_LOG(LogTemp, Warning, TEXT("HP: %f"), Attributes->GetCurrentHP());
    }
}

void AMobaSelectable::HandleResourceChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
    if (bAbilitiesInitialized)
    {
        OnResourceChanged(DeltaValue, EventTags);
    }
}

void AMobaSelectable::HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags)
{
    // Update the character movement's walk speed
    GetCharacterMovement()->MaxWalkSpeed = GetMoveSpeed();
    if (bAbilitiesInitialized)
    {
        OnMoveSpeedChanged(DeltaValue, EventTags);
    }
}




float AMobaSelectable::GetBaseHP() const
{
    if (Attributes)
        return Attributes->GetBaseHP();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));

    return 9.f;
}

float AMobaSelectable::GetMaxHP() const
{
    if (Attributes)
        return Attributes->GetMaxHP();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));

    return 9.f;
}

float AMobaSelectable::GetCurrentHP() const
{
    if (Attributes)
        return Attributes->GetCurrentHP();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));

    return 9.f;
}

float AMobaSelectable::GetLevel() const
{
    if (Attributes)
        return Attributes->GetLevel();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));
    return 9.f;
}
float AMobaSelectable::GetBaseAtkSpeed() const
{
    if (Attributes)
        return Attributes->GetBaseAtkSpeed();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));
    return 9.f;
}

float AMobaSelectable::GetAtkSpeed() const
{
    if (Attributes)
        return Attributes->GetAtkSpeed();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));
    return 9.f;
    return 9.f;
}
float AMobaSelectable::GetBaseMoveSpeed() const
{
    if (Attributes)
        return Attributes->GetBaseMoveSpeed();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));
    return 9.f;
}
float AMobaSelectable::GetMoveSpeed() const
{
    if (Attributes)
        return Attributes->GetMoveSpeed();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));
    return 9.f;
}
float AMobaSelectable::GetAtkDamage() const
{
    if (Attributes)
        return Attributes->GetAtkDamage();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));
    return 9.f;
}
float AMobaSelectable::GetAtkRange() const
{
    if (Attributes)
        return Attributes->GetAtkRange();
    else
        UE_LOG(LogTemp, Error, TEXT("No AttributeSet."));
    return 9.f;
}
