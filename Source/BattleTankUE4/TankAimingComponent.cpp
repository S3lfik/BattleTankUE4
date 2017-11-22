// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
	: TankBarrel(nullptr)
	, TankTurret(nullptr)
	, FiringState(EFiringState::Reloading)
	, AimDirection(0.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// ...

	LastFireTime = FPlatformTime::Seconds();
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (RoundsLeft <= 0)
		FiringState = EFiringState::OutOfAmmo;
	else if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds)
		FiringState = EFiringState::Reloading;
	else if ( IsBarrelMoving())
		FiringState = EFiringState::Aiming;
	else
		FiringState = EFiringState::Locked;

}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(TankBarrel) || !ensure(TankTurret))
		return;

	FVector LaunchVelocity;
	FVector StartLocation = TankBarrel->GetSocketLocation(FName("ProjectileOut"));

	if (!UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
		false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))//, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), true))
	{
		return;
	}

	AimDirection = LaunchVelocity.GetSafeNormal();
	AimTowardsVector(AimDirection);
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet)
		return;

	TankBarrel = BarrelToSet;
	TankTurret = TurretToSet;
}

void UTankAimingComponent::AimTowardsVector(FVector AimDirection)
{
	if (!ensure(TankBarrel) || !ensure(TankTurret))
		return;

	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator RotationDiff = AimAsRotator - BarrelRotator;

	TankBarrel->Elevate(RotationDiff.Pitch);

	if( FMath::Abs(RotationDiff.Yaw) < 180.f)
		TankTurret->Rotate(RotationDiff.Yaw);
	else
		TankTurret->Rotate(-RotationDiff.Yaw);
}

bool UTankAimingComponent::IsBarrelMoving() const
{
	if (!ensure(TankBarrel))
		return false;

	auto Forward = TankBarrel->GetForwardVector();

	return !Forward.Equals(AimDirection, 0.01f);
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming )
	{
		if (!ensure(TankBarrel && ProjectileRef))
			return;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileRef
			, TankBarrel->GetSocketLocation(FName("ProjectileOut"))
			, TankBarrel->GetSocketRotation(FName("ProjectileOut")));

		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

		--RoundsLeft;
	}
}