// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"

class UFloatingPawnMovement;
class USphereComponent;


UCLASS()
class ACameraPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float PitchChangeRate =90.0f;
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float YawRate = 150.0f;
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float PanRate = 50.0f;
	
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float ScreenEdgePanZonePercent = 5.f;

	UPROPERTY(EditAnywhere, Category = "Bounds")
	float MaxPitch = 335.0f;
	UPROPERTY(EditAnywhere, Category = "Bounds")
	float MinPitch = 285.0f;
	UPROPERTY(EditAnywhere, Category = "Bounds")
	float MaxZoom = 3000.0f;
	UPROPERTY(EditAnywhere, Category = "Bounds")
	float MinZoom = 300.0f;


	void ChangePitch(float magnitude);
	void Yaw(float magnitude);
	void EngageRotation();
	void DisengageRotation();
	void Orbit(float magnitude);
	bool rotationMode = false;

	FVector2D mouseScreenLocationGrab;	
	UFloatingPawnMovement* MovementComponent;
	USphereComponent* CustomCollisionComponent;

	UPROPERTY()
	APlayerController* PC;
	UPROPERTY()
	float XPanZone;
	UPROPERTY()
	float YPanZone;
	UPROPERTY()
	int32 ScreenSizeX = 0;
	UPROPERTY()
	int32 ScreenSizeY = 0;
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float CamSpeed = 1000.f;
	UPROPERTY(EditAnywhere, Category = "Sensitivity")
	float ZoomRate = 3000.f;
	UFUNCTION()
	FVector GetCameraPanDirection();
	UFUNCTION()
	void PanCamera(FVector PanDirection);
	UFUNCTION()
	void ZoomIn();
	UFUNCTION()
	void ZoomOut();

};
