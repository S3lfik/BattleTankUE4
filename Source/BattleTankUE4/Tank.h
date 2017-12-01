// Fill out your copyright notice in the Description page of Project Settings.
//Tank.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANKUE4_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealthPercentage();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;
};
