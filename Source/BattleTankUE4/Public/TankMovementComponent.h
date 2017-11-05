// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "Runtime/Engine/Classes/GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKUE4_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UTankMovementComponent();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack* leftTrack, UTankTrack* rightTrack);

private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

private:
	UTankTrack* TrackLeft;
	UTankTrack* TrackRight;
	
};
