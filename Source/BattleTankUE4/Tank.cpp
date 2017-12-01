// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
	: StartingHealth(100)
	, CurrentHealth(StartingHealth)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageRounded = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamageRounded, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
		UE_LOG(LogTemp, Warning, TEXT("Tank is dead!"));

	return (float)DamageToApply;
}

float ATank::GetCurrentHealthPercentage()
{
	//if (!ensure(StartingHealth))
	//	return 0.f;

	float HealthPercent = (float)CurrentHealth / (float)StartingHealth;

	return HealthPercent;
}

