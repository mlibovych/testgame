// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
	MakeShot();
}

void ABaseWeaponActor::MakeShot()
{
	if (!GetWorld()) return;

	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;
	const auto Controller = Player->GetController<APlayerController>();
	if (!Controller) return;

	FVector ViewLocation;
	FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	
	FTransform SocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);
	FVector TraceStart = ViewLocation;//SocketTransform.GetLocation();
	FVector TraceDirection = ViewRotation.Vector();//SocketTransform.GetRotation().GetForwardVector();
	FVector TraceEnd = TraceStart + TraceDirection * TraceMaxLength;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());
	FHitResult Result;
	GetWorld()->LineTraceSingleByChannel(Result, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);

	if (Result.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), Result.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), Result.ImpactPoint, 10.0f, 24, FColor::Blue, false, 5.0f);

		if (Result.GetActor())
		{
			Result.GetActor()->TakeDamage(Damage, FDamageEvent{}, Controller, GetOwner());
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), SocketTransform.GetLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}


