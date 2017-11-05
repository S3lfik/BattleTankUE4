// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUE4_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float MaxElevationDegreesPerSecond = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float MaxElevationDegree = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = Aiming)
	float MinElevationDegree = 0.f;
};
