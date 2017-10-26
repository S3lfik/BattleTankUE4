// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"



void UTankBarrel::Elevate(float RelativeElevation)
{
	RelativeElevation = FMath::Clamp(RelativeElevation, -1.f, 1.f);
	auto ElevationDiff = RelativeElevation * MaxElevationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawElevation = RelativeRotation.Pitch + ElevationDiff;

	RawElevation = FMath::Clamp(RawElevation, MinElevationDegree, MaxElevationDegree);

	SetRelativeRotation(FRotator(RawElevation, 0.f, 0.f));
}
