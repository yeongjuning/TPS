// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"
#include "TPSGameModeBase.h"
#include "TPSGameInstance.h"
#include "WeaponBase.h"
#include "AttackComponent.h"

const int32 ATPSCharacter::MaxWeaponSlot = 3;

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackComponent = CreateDefaultSubobject<UAttackComponent>(FName(TEXT("Attack Component")));
	AttackComponent->SetupAttachment(GetMesh());

	Weapon = nullptr;
}

void ATPSCharacter::SetCurrentWeaponState(int32 SlotIdx)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;

	switch (SlotIdx)
	{
	case 0:
		bIsRifle = true;
		break;
	case 1:
		bIsKnife = true;
		break;
	case 2:
		bIsGrenade = true;
		break;
	default:
		break;
	}
}

void ATPSCharacter::SetCurrentWeaponSlot(int32 SlotIdx)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;
		
	CurrentWeaponSlot = SlotIdx;
	UE_LOG(LogTemp, Log, TEXT("Set Current WeaponSlot : %d"), CurrentWeaponSlot);
}

AWeaponBase* ATPSCharacter::GetWeapon(int32 SlotIdx) const
{
	if (EquipedWeapons.IsValidIndex(SlotIdx))
		return EquipedWeapons[SlotIdx];
	else
		return nullptr;
}

AWeaponBase* ATPSCharacter::GetCurrentWeapon() const
{
	int32 Slot = GetCurrentWeaponSlot();

	return GetWeapon(Slot);
}

float ATPSCharacter::GetAttackSpeed() const
{
	if (EquipedWeapons.IsValidIndex(CurrentWeaponSlot) == false)
		return 0.0f;

	if (IsValid(EquipedWeapons[CurrentWeaponSlot]) == false)
		return 0.0f;

	return EquipedWeapons[CurrentWeaponSlot]->WeaponPreset.AttackSpeed;
}

void ATPSCharacter::SetEquipedWeaponId(int32 WeaponIdsIndex, int32 SlotIdx)
{
	if (EquipedWeapons.IsValidIndex(SlotIdx) == false)
		return;

	WeaponIds[WeaponIdsIndex] = TPSGameInstance->GetWeaponId(SlotIdx + 1);
	UE_LOG(LogTemp, Log, TEXT("EquipedWeaponIds->WeaponIds[%d] :: %s"), WeaponIdsIndex, *WeaponIds[WeaponIdsIndex].ToString());
}

FName ATPSCharacter::GetEquipedWeaponIds(int32 WeaponIdsIndex, int32 SlotIdx) const
{
	if (EquipedWeapons.IsValidIndex(SlotIdx))
		return WeaponIds[WeaponIdsIndex];
	else
		return FName();
}

void ATPSCharacter::Attack_Implementation()
{
	AttackComponent->Attack();
}

void ATPSCharacter::StopAttack_Implementation()
{
	AttackComponent->StopAttack();
}

void ATPSCharacter::Reload_Implementation()
{
	AttackComponent->StartReload();
}

void ATPSCharacter::CompleteReload_Implementation()
{
	AttackComponent->CompleteReload();
}

void ATPSCharacter::Dead_Implementation()
{
	bIsDead = true;
	GetWorldTimerManager().SetTimer(DeathTimerHandler, this, &ATPSCharacter::OnDeathTimerComplete, 3.0f);
	EGamePlayingState GamePlayingState = EGamePlayingState::GameOver;
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	EquipedWeapons.SetNum(MaxWeaponSlot);
	WeaponIds.SetNum(MaxWeaponSlot);

	TPSGameInstance = Cast<UTPSGameInstance>(GetWorld()->GetGameInstance());
	TPSGameMode = GetWorld()->GetAuthGameMode<ATPSGameModeBase>();

	CharStatus = NewObject<UCharacterStatus>(this, TEXT("Character Status"));

	if (IsValid(CharStatus))
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

void ATPSCharacter::OnDeathTimerComplete()
{
	// Hides visible components
	SetActorHiddenInGame(true);
	// Disables collision components
	SetActorEnableCollision(false);
	// Stops the Actor from ticking
	SetActorTickEnabled(false);
}