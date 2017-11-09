// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
	: TankBarrel(nullptr)
	, TankTurret(nullptr)
	, FiringState(EFiringState::Reloading)
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
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OwnerName = GetOwner()->GetName();
	
	if (!ensure(TankBarrel))
	{

		FVector LaunchVelocity;
		FVector StartLocation = TankBarrel->GetSocketLocation(FName("ProjectileOut"));

		if (!UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, 
			false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))//, FCollisionResponseParams::DefaultResponseParam, TArray<AActor*>(), true))
		{
			return;
		}

		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	if (!BarrelToSet || !TurretToSet)
		return;

		TankBarrel = BarrelToSet;
		TankTurret = TurretToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(TankBarrel))
		return;

	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator RotationDiff = AimAsRotator - BarrelRotator;

	TankBarrel->Elevate(RotationDiff.Pitch);
	TankTurret->Rotate(RotationDiff.Yaw);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!ensure(TankTurret))
		return;

	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator RotationDiff = AimAsRotator - BarrelRotator;

	TankTurret->Rotate(RotationDiff.Yaw);
}

