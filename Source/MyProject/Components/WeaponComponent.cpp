// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapons/BaseWeaponActor.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	CurrentWeapon = GetWorld()->SpawnActor<ABaseWeaponActor>(WeaponClass);
	if (CurrentWeapon)
	{
		ACharacter* Character = Cast<ACharacter>(GetOwner());

		if (Character)
		{
			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		
			CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
		}
	}
}

void UWeaponComponent::Fire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}
