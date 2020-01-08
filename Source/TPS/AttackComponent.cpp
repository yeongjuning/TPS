// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "TPSCharacter.h"

//const int32 UAttackComponent::MaxWeaponSlot = 3;

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UAttackComponent::StartReload()
{
	AWeaponBase* Weapon = PlayerCharacter->GetCurrentWeapon();
	AAmmoInventory* AmmoInven = Cast<AAmmoInventory>(AAmmoInventory::StaticClass());

	if (IsValid(Weapon) == false)
		return;

	if (Weapon->Magazine >= Weapon->WeaponPreset.MagazineCount)
		return;

	if (AmmoInven->GetAmmo(Weapon->WeaponPreset.WeaponKind) <= 0)
		return;

	bReloading = true;
	OnStartReload.Broadcast();
	UE_LOG(LogTemp, Log, TEXT("Start Reload"));
}

void UAttackComponent::CompleteReload()
{
	bReloading = false;
	
	AWeaponBase* Weapon = PlayerCharacter->GetCurrentWeapon();
	AAmmoInventory* AmmoInven = Cast<AAmmoInventory>(AAmmoInventory::StaticClass());

	if (IsValid(Weapon) == false)
		return;

	Weapon->Magazine = AmmoInven->ConsumeAmmo(Weapon->WeaponPreset.WeaponKind, Weapon->WeaponPreset.MagazineCount);

	OnCompleteReload.Broadcast();

	UE_LOG(LogTemp, Log, TEXT("Completed Reload"));
}

void UAttackComponent::Attack()
{
	AWeaponBase* Weapon = PlayerCharacter->GetCurrentWeapon();
	
	if (IsValid(Weapon))
	{	
		int32 CurrentAmmo = Weapon->AmmoInven->GetAmmo(Weapon->WeaponKind);
		Weapon->AmmoInven->ConsumeAmmo(Weapon->WeaponKind, 1);		// Ammo 소비

		if (CurrentAmmo <= 0)
		{
			Weapon->IsAmmoEmpty();
			UE_LOG(LogTemp, Log, TEXT("현재 남은 Ammo가 존재하지 않습니다."));
			StopAttack();
		}

		bCanAttack = true;
		Weapon->FireAndAttack();
	}
}

void UAttackComponent::StopAttack()
{
	bCanAttack = false;
	UE_LOG(LogTemp, Log, TEXT("Stop Attack"));
}

void UAttackComponent::OnWaitAttackTimerEnd()
{
	StopAttack();
}

// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ATPSCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	TPSGameMode = GetWorld()->GetAuthGameMode<ATPSGameModeBase>();
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

