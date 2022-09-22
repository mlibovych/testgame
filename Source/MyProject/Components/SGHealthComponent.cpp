// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SGHealthComponent.h"

USGHealthComponent::USGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);

	if (AActor* ComponentOwner = GetOwner()) {
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USGHealthComponent::OnTakeAnyDamageHandle);
	}
}

void USGHealthComponent::OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (IsDead() || Damage <= 0.0f)
	{
		return;
	}
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);

	if(IsDead())
	{
		OnDeath.Broadcast();
	}
		
}


