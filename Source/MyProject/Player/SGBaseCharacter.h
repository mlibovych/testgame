// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeaponActor.h"
#include "SGHealthComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SGBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USGHealthComponent;
class UTextRenderComponent;
class ABaseWeaponActor;
class UWeaponComponent;

UCLASS()
class MYPROJECT_API ASGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASGBaseCharacter(const FObjectInitializer &ObjInit);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	USGHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UTextRenderComponent* TextRenderComponent;

	UPROPERTY(EditDefaultsOnly, Category="Animation")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	FVector2D LandedDamageVelocity = FVector2D(500.0f, 1600.0f);

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	FVector2D LandedDamage = FVector2D(5.0f, 100.0f);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Weapon")
	UWeaponComponent* WeaponComponent;
	
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Movement")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection() const;

	UFUNCTION(BlueprintCallable, Category="Life")
	void OnDeath();
	
	UFUNCTION(BlueprintCallable, Category="Life")
	void OnHealthChanged(float Health);

	UFUNCTION(BlueprintCallable, Category="Life")
	void OnGroundLanded(const FHitResult& Hit);

private:
	bool WantsToRun {false};
	bool IsMovingForward {false};
	
	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void LookUp(float Amount);
	void TurnAround(float Amount);

	void OnStartRunning();
	void OnStopRunning();
};
