// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SGCharacterMovementComponent.h"
#include "Player/SGBaseCharacter.h"

float USGCharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();
	const ASGBaseCharacter* Player = Cast<ASGBaseCharacter> (GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
