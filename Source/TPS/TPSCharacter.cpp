// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharStatus = CreateDefaultSubobject<UCharacterStatus>(TEXT("Character Status"));
	AttackComponent = CreateDefaultSubobject<UAttackComponent>(FName(TEXT("Attack Component")));
	
	Weapon = nullptr;
}

void ATPSCharacter::Attack_Implementation()
{
	AttackComponent->Attack();
}

void ATPSCharacter::StopAttack_Implementation()
{
	AttackComponent->StopAttack();
}

void ATPSCharacter::Dead_Implementation()
{
	bIsDead = true;
	GetWorldTimerManager().SetTimer(DeathTimerHandler, this, &ATPSCharacter::OnDeathTimerComplete, 3.0f);
	EGamePlayingState GamePlayingState = EGamePlayingState::GameOver;
}

void ATPSCharacter::Reload_Implementation()
{
	bIsReload = true;
	GetWorldTimerManager().SetTimer(ReloadTimerHandler, this, &ATPSCharacter::StopReload, 0.8f);
}

void ATPSCharacter::StopReload_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("StopReload"));
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurHP = CharStatus->GetCurrentHealth();
}

// Called every frame
void ATPSCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

float ATPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCasuser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCasuser);

	if (bIsDead)
		return 0.0f;

	float HealthOfDamage = CharStatus->HealthManager(DamageAmount, CurHP);

	if (HealthOfDamage <= 0.0f)
	{
		CharStatus->IsHealthZero();
		bIsDead = true;
	}

	return DamageAmount;
}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATPSCharacter::OnReloadTimerComplete()
{
	bIsReload = false;
}

void ATPSCharacter::OnDeathTimerComplete()
{
	// Hides visible components
	SetActorHiddenInGame(true);
	// Disables collision components
	SetActorEnableCollision(false);
	// Stops the Actor from ticking
	SetActorTickEnabled(false);
}