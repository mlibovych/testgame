// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API USGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	virtual float GetMaxSpeed() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Running", meta = (ClampMin = 1.5, ClampMax = 10))
	float RunModifier = 2.5;	
private:
	
};
