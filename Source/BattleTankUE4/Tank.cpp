// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"

// Sets default values
ATank::ATank()
	: TankBarrel(nullptr)
	, TankAimingComponent(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(FVector HitLocation)
{

	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
	}
}

void ATank::SetBarrel(UTankBarrel * BarrelToSet)
{
	if (BarrelToSet)
	{
		TankAimingComponent->SetBarrelRef(BarrelToSet);
		TankBarrel = BarrelToSet;
	}
}

void ATank::SetTurret(UTankTurret * TurretToSet)
{
	if (TurretToSet)
		TankAimingComponent->SetTurretRef(TurretToSet);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (!TankBarrel || !isReloaded)
		return;

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileRef
		, TankBarrel->GetSocketLocation(FName("ProjectileOut"))
		, TankBarrel->GetSocketRotation(FName("ProjectileOut")));

	if (Projectile)
		Projectile->LaunchProjectile(LaunchSpeed);

	LastFireTime = FPlatformTime::Seconds();
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

