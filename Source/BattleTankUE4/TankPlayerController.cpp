// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
		return;

	FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	AimTowardCrosshair();
}

void ATankPlayerController::AimTowardCrosshair()
{
	auto PossessedTank = GetPawn();
	if (!ensure(PossessedTank))
		return;

	auto AimingComponent = PossessedTank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent))
		return;

	FVector OutHitLocation;

	if ( IsSightRayHitLandscape(OutHitLocation) )
	{
		AimingComponent->AimAt(OutHitLocation);
	}
}

bool ATankPlayerController::IsSightRayHitLandscape(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.f);
	int32 ViewportWidth, ViewportHeight;
	GetViewportSize(ViewportWidth, ViewportHeight);
	FVector2D CrosshairLocation = FVector2D(ViewportWidth * CrosshairXRatio, ViewportHeight * CrosshairYRatio);
	
	return GetLookHitResultLocation(CrosshairLocation, OutHitLocation);
}

bool ATankPlayerController::GetLookHitResultLocation(FVector2D CrosshairLocation, FVector & OutHitLocation) const
{
	FVector CrosshairWorldLocation;
	FVector LookDirection;
	
	FHitResult LookHitResult;
	FViewLine ViewLine;

	DeprojectScreenPositionToWorld(CrosshairLocation.X, CrosshairLocation.Y, CrosshairWorldLocation, LookDirection);

	ViewLine.ViewLineStart = PlayerCameraManager->GetCameraLocation();
	ViewLine.ViewLineEnd = CrosshairWorldLocation + LookDirection * ViewLength;
	GetWorld()->LineTraceSingleByChannel(LookHitResult, ViewLine.ViewLineStart, ViewLine.ViewLineEnd, ECC_Camera);

	

	AActor* HitActor = LookHitResult.GetActor();
	if (HitActor)
	{
		OutHitLocation = LookHitResult.Location;
		return true;
	}

	return false;
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		ATank* PosessedTank = Cast<ATank>(InPawn);

		if (!ensure(PosessedTank))
			return;

		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPosessedTankDeath);
	}
}

void ATankPlayerController::OnPosessedTankDeath()
{
	StartSpectatingOnly();
}
