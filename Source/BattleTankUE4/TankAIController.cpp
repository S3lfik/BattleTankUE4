// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		ATank* ControlledTank = Cast<ATank>(GetPawn());

		if (ControlledTank)
		{
			ControlledTank->AimAt(PlayerTank->GetActorLocation());
			ControlledTank->Fire();
		}
	}
}

