// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeaponActor.generated.h"

class USkeletalMeshComponent;

UCLASS()
class MYPROJECT_API ABaseWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeaponActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

public:	
	virtual void Fire();
};
