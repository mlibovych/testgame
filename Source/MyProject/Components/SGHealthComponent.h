// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGHealthComponent();

	float GetHealth() { return Health; };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 100.0f, ClampMax = 1000.0f))
	float MaxHealth = 100.0f;;

	UFUNCTION()
	void OnTakeAnyDamageHandle(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	bool IsDead() { return Health <= 0.0f; }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;
protected:
	virtual void BeginPlay() override;

	

private:
	float Health =0.0f;
};