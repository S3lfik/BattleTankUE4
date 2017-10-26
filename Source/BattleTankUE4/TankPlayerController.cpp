// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is posessed by player"), *(ControlledTank->GetName()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player doesn't posses any tank"));
	}
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
	if (!Tank) return;

	FVector OutHitLocation;

	if ( IsSightRayHitLandscape(OutHitLocation) )
	{
		Tank->AimAt(OutHitLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player doesn't set HitLocation!!"));
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
		UE_LOG(LogTemp, Warning, TEXT("ViewLineStart: %s"), *(ViewLine.ViewLineStart.ToString()));
		UE_LOG(LogTemp, Warning, TEXT("HitTest: %s"), *(LookDirection.ToString()));
		UE_LOG(LogTemp, Warning, TEXT("ViewLineEnd: %s"), *(ViewLine.ViewLineEnd.ToString()));
		OutHitLocation = HitActor->GetTargetLocation();
		return true;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("HitTest Failed: %s"), *(HitActor->GetTargetLocation().ToString()));

	return false;
}
