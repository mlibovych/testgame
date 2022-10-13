// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/SGBaseCharacter.h"

#include "WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SGCharacterMovementComponent.h"
#include "Components/SGHealthComponent.h"
#include "Components/TextRenderComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)

// Sets default values
ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer &ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USGHealthComponent>("HealthComponent");

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
	TextRenderComponent->SetupAttachment(GetRootComponent());

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(HealthComponent->GetHealth());
	HealthComponent->OnDeath.AddUObject(this, &ASGBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASGBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ASGBaseCharacter::OnGroundLanded);
}

void ASGBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = GetCharacterMovement()->Velocity.Z;

	if (-FallVelocityZ < LandedDamageVelocity.X)
		return;

	const auto Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, -FallVelocityZ);
	TakeDamage(Damage, FDamageEvent{}, nullptr, nullptr);
}

void ASGBaseCharacter::OnDeath()
{
	PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ASGBaseCharacter::OnHealthChanged(float Health)
{
	TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Called every frame
void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASGBaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ASGBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASGBaseCharacter::TurnAround);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASGBaseCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASGBaseCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASGBaseCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UWeaponComponent::Fire);
}

void ASGBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0.0f;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASGBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}

void ASGBaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void ASGBaseCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

void ASGBaseCharacter::OnStartRunning()
{
	WantsToRun = true;
}

void ASGBaseCharacter::OnStopRunning()
{
	WantsToRun = false;
}

bool ASGBaseCharacter::IsRunning() const
{
	return IsMovingForward && WantsToRun && !GetVelocity().IsZero();
}

float ASGBaseCharacter::GetMovementDirection() const
{
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

	return FMath::RadiansToDegrees(AngleBetween) * FMath::Sign(CrossProduct.Z);
}


