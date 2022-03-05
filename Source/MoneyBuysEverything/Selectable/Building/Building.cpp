// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"

#include "GameFramework/Actor.h"

ABuilding::ABuilding()
{ 

 }
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::HandleDestruction()
{
	UE_LOG(LogTemp, Warning, TEXT("Structure Destroyed!"));
	// --- Universal functionality ---
	// Play death effects particle, sound and camera shake. 
	//UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	//UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	//GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

}

void ABuilding::Destroyed()
{
	HandleDestruction();
}
