// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeaponActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaponComponent();

	void Fire();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	TSubclassOf<ABaseWeaponActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category="Weapon")
	FName  WeaponAttachPointName;

private:	
	void SpawnWeapon();

	UPROPERTY()
	ABaseWeaponActor* CurrentWeapon = nullptr;
};
