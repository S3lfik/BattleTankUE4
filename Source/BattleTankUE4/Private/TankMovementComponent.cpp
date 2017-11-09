// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


UTankMovementComponent::UTankMovementComponent()
	: TrackLeft(nullptr)
	, TrackRight(nullptr)
{
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(TrackLeft && TrackRight))
		return;

	TrackLeft->SetThrottle(Throw);
	TrackRight->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(TrackLeft && TrackRight))
		return;

	TrackLeft->SetThrottle(Throw);
	TrackRight->SetThrottle(-Throw);
}

void UTankMovementComponent::Initialise(UTankTrack * leftTrack, UTankTrack * rightTrack)
{
	if (!ensure(leftTrack && rightTrack))
		return;

	TrackLeft = leftTrack;
	TrackRight = rightTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto ForwardVector = GetOwner()->GetActorForwardVector();
	auto ForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(ForwardVector, ForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RotationThrow = FVector::CrossProduct(ForwardVector, ForwardIntention);
	IntendTurnRight(RotationThrow.Z);
}

