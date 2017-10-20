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
}

bool ATankPlayerController::IsSightRayHitLandscape(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(0.f);
	CrosshairXRatio;
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
	FVector CrosshairWorldDirction;
	
	FHitResult LookHitResult;
	FViewLine ViewLine;

	DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CrosshairWorldLocation, CrosshairWorldDirction);

	ViewLine.ViewLineStart = CrosshairWorldLocation;
	ViewLine.ViewLineEnd = CrosshairWorldLocation + CrosshairWorldDirction * ViewLength;
	GetWorld()->LineTraceSingleByChannel(LookHitResult, ViewLine.ViewLineStart, ViewLine.ViewLineEnd, ECC_Visibility);

	AActor* HitActor = LookHitResult.GetActor();
	if (HitActor)
	{
		OutHitLocation = HitActor->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Crosshair Looks At : %s"), *(HitActor->GetName()));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Crosshair Looks At Nothing"));
	}
	return false;
}
