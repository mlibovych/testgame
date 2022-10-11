// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"

ABaseWeaponActor::ABaseWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(SkeletalMeshComponent);

}

void ABaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseWeaponActor::Fire()
{
	UE_LOG(LogTemp, Error, TEXT("FIRE"))
}


