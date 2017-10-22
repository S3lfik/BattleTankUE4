// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Barrel = nullptr;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("AimingComponent is ready for %s"), *(GetOwner()->GetName()));
	// ...
	
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OwnerName = GetOwner()->GetName();
	
	if (Barrel)
		UE_LOG(LogTemp, Warning, TEXT("%s Aims From %s At: %s"), 
			*(OwnerName),
			*(Barrel->GetComponentLocation().ToCompactString()), 
			*(HitLocation.ToCompactString()));
}

void UTankAimingComponent::SetBarrelRef(UStaticMeshComponent * BarrelToSet)
{
	if (BarrelToSet)
		Barrel = BarrelToSet;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

