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
	ATank* ControlledTank = Cast<ATank>(GetPawn());

	if (!ensure(PlayerTank && ControlledTank)) 
		return;
		
	MoveToActor(PlayerTank, AcceptanceRadius);

	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();


}

