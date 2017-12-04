// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"

// Sets default values
ATank::ATank()
	: StartingHealth(100)
	, CurrentHealth(0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamageRounded = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamageRounded, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return (float)DamageToApply;
}

float ATank::GetCurrentHealthPercentage()
{
	if (!StartingHealth)
		return 0.f;

	float HealthPercent = (float)CurrentHealth / (float)StartingHealth;

	return HealthPercent;
}

