// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */

USTRUCT()
struct FViewLine
{
	GENERATED_BODY()

		UPROPERTY()
		FVector ViewLineStart;

	UPROPERTY()
		FVector ViewLineEnd;
};

UCLASS()
class BATTLETANKUE4_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ATank* GetControlledTank() const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AimTowardCrosshair();

private:
	bool IsSightRayHitLandscape(FVector& OutHitLocation) const;

	bool GetLookHitResultLocation(FVector2D CrosshairLocation, FVector & OutHitLocation) const;

private:
	UPROPERTY(EditAnywhere)
	float CrosshairXRatio = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYRatio = 0.333f;

	UPROPERTY(EditAnywhere)
	float ViewLength = 1000000.f;
};
