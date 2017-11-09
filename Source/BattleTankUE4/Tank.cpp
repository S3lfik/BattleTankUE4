// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
	: TankBarrel(nullptr)
	, TankAimingComponent(nullptr)
	, TankMovementComponent(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{

	if (!ensure(TankAimingComponent))
		return;
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(TankBarrel))
		return;

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileRef
			, TankBarrel->GetSocketLocation(FName("ProjectileOut"))
			, TankBarrel->GetSocketRotation(FName("ProjectileOut")));

			Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

