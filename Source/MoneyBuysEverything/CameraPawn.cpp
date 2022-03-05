// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EngineUtils.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CustomCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_Component1"));
	CustomCollisionComponent->InitSphereRadius(100.0f);
	CustomCollisionComponent->CanCharacterStepUpOn = ECB_No;
	CustomCollisionComponent->SetCanEverAffectNavigation(false);
	CustomCollisionComponent->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	RootComponent = CustomCollisionComponent;	

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement_Component1"));
	MovementComponent->UpdatedComponent = CustomCollisionComponent;

	
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController());
	if(PC==nullptr) return;
	PC->GetViewportSize(ScreenSizeX,ScreenSizeY);
	XPanZone = ScreenSizeX * ScreenEdgePanZonePercent / 100;
	YPanZone = XPanZone;


}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (rotationMode) //Main Camera rotation calls
	{
		// Orbit((mouseScreenLocationGrab.X - mouseLocation.X) / ScreenSizeX);
		// ChangePitch((mouseScreenLocationGrab.Y - mouseLocation.Y)*-1 / ScreenSizeX);
	}
	else //  Mouse on screen edge pan
	{	
		PanCamera(GetCameraPanDirection());
	}

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(InputComponent);
	// InputComponent->BindAxis("Pan Forward", this, &ACameraPawn::PanForward);
	// InputComponent->BindAxis("Pan Right", this, &ACameraPawn::PanRight);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &ACameraPawn::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &ACameraPawn::ZoomOut);

	InputComponent->BindAction("Rotate Camera", IE_Pressed, this, &ACameraPawn::EngageRotation);
	InputComponent->BindAction("Rotate Camera", IE_Released, this, &ACameraPawn::DisengageRotation);

}


void ACameraPawn::ChangePitch(const float magnitude)
{
	if (magnitude != 0 && rotationMode && Controller)
		if (magnitude < 0 && GetControlRotation().Pitch < MaxPitch || magnitude > 0 && GetControlRotation().Pitch > MinPitch)
			AddControllerPitchInput(magnitude * PitchChangeRate * GetWorld()->GetDeltaSeconds());		
}

void ACameraPawn::Yaw(const float magnitude)
{
	if (magnitude != 0 && rotationMode && Controller)
	{
		AddControllerYawInput(magnitude * YawRate *GetWorld()->GetDeltaSeconds());
	}		
			
}

void ACameraPawn::Orbit(const float magnitude)
{
	if (magnitude != 0 && rotationMode && Controller)
	{
		if (PC != nullptr)
		{
			AddControllerYawInput(magnitude * YawRate *GetWorld()->GetDeltaSeconds());
			AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), magnitude * -(YawRate/4)* GetWorld()->GetDeltaSeconds());
		}
	}

}


void ACameraPawn::ZoomIn()
{

	FVector ZoomVector = FVector(0,0,-1);
	if (!rotationMode && PC)
		{
		if (GetActorLocation().Z > MinZoom && GetActorLocation().Z < MaxZoom)
		AddActorWorldOffset(ZoomVector*ZoomRate*GetWorld()->GetDeltaSeconds());	
	}
}

void ACameraPawn::ZoomOut()
{
	FVector ZoomVector = FVector(0,0,1);
	if (!rotationMode && PC)
	{
		if (GetActorLocation().Z > MinZoom && GetActorLocation().Z < MaxZoom)
		AddActorWorldOffset(ZoomVector*ZoomRate*GetWorld()->GetDeltaSeconds());	
	}
}


void ACameraPawn::EngageRotation()
{	
	if (Controller)
	{
		if (PC != nullptr)
		{				
			FVector2D mousePosition;
			if (PC->GetMousePosition(mousePosition.X, mousePosition.Y))
			{
				mouseScreenLocationGrab = mousePosition;
				rotationMode = true;
			}
		}
	}
}

void ACameraPawn::DisengageRotation()
{
	rotationMode = false;
}

FVector ACameraPawn::GetCameraPanDirection()
{
	float MousePosX;
	float MousePosY;
	float CamDirectionX=0;
	float CamDirectionY=0;

	if(PC)
	{
		if(PC->GetMousePosition(MousePosX,MousePosY))
			{if(MousePosX <= XPanZone && MousePosX>=0)
			{
				CamDirectionY = -1.f;
			}
			else if(MousePosX >= ScreenSizeX - XPanZone)
			{
				CamDirectionY = 1.f;
			}
			if(MousePosY <= YPanZone && MousePosY>=0)
			{
				CamDirectionX = 1.f;
			}
			else if(MousePosY >= ScreenSizeY - YPanZone)
			{
				CamDirectionX = -1.f;
			}
		}
	}

	return FVector(CamDirectionX,CamDirectionY,0);
}

void ACameraPawn::PanCamera(FVector PanDirection)
{
	if(PanDirection == FVector::ZeroVector)
	{
		return;
	}
	else
	{
		AddActorWorldOffset(this->GetCameraPanDirection()*CamSpeed*GetWorld()->GetDeltaSeconds());
	}

}

