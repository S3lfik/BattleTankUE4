// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
	: TankBarrel(nullptr)
	, TankTurret(nullptr)
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
	UE_LOG(LogTemp, Warning, TEXT("AimingComponent is ready for %s"), *(GetOwner()->GetName()));
	// ...
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	auto OwnerName = GetOwner()->GetName();
	
	if (TankBarrel)
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

void UTankAimingComponent::SetBarrelRef(UTankBarrel * BarrelToSet)
{
	if (BarrelToSet)
		TankBarrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretRef(UTankTurret * TurretToSet)
{
	if (TurretToSet)
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
	if (!TankBarrel)
		return;

	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator RotationDiff = AimAsRotator - BarrelRotator;

	TankBarrel->Elevate(RotationDiff.Pitch);
	TankTurret->Rotate(RotationDiff.Yaw);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	if (!TankTurret)
		return;
	FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator RotationDiff = AimAsRotator - BarrelRotator;

	TankTurret->Rotate(RotationDiff.Yaw);
}

