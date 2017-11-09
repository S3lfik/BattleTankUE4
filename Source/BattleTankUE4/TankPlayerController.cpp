// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent))
		return;

	FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardCrosshair();
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	ATank* Tank = GetControlledTank();
	if (!ensure(Tank))
		return;

	FVector OutHitLocation;

	if ( IsSightRayHitLandscape(OutHitLocation) )
	{
		Tank->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::IsSightRayHitLandscape(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.f);
	int32 ViewportWidth, ViewportHeight;
	GetViewportSize(ViewportWidth, ViewportHeight);
	FVector2D CrosshairLocation = FVector2D(ViewportWidth * CrosshairXRatio, ViewportHeight * CrosshairYRatio);
	
	if (GetLookHitResultLocation(CrosshairLocation, OutHitLocation))
		return true;
	else
		return false;
}

bool ATankPlayerController::GetLookHitResultLocation(FVector2D CrosshairLocation, FVector & OutHitLocation) const
{
	FVector CrosshairWorldLocation;
	FVector LookDirection;
	
	FHitResult LookHitResult;
	FViewLine ViewLine;

	DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CrosshairWorldLocation, LookDirection);

	ViewLine.ViewLineStart = PlayerCameraManager->GetCameraLocation();//CrosshairWorldLocation;
	ViewLine.ViewLineEnd = CrosshairWorldLocation + LookDirection * ViewLength;
	GetWorld()->LineTraceSingleByChannel(LookHitResult, ViewLine.ViewLineStart, ViewLine.ViewLineEnd, ECC_Visibility);

	

	AActor* HitActor = LookHitResult.GetActor();
	if (HitActor)
	{
		OutHitLocation = LookHitResult.Location;
		return true;
	}

	return false;
}
