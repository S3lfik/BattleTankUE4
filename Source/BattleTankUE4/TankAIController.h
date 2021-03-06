// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKUE4_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:	
	virtual void BeginPlay() override;	
	virtual void Tick(float DeltaTime) override;
	virtual void SetPawn(APawn* InPawn) override;

private:

	UFUNCTION()
	void OnPosessedTankDeath();

private:

	// Acceptance distance to get to target AActor
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float AcceptanceRadius = 10000;
};

