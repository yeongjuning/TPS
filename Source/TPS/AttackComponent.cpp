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

	if (IsValid(Weapon) == false)
		return;

	if (Weapon->WeaponPreset.MagazineCount <= 0)
		return;

	if (AmmoIsAtMaximum(Weapon))
		return;

	bReloading = true;
	
	GetWorld()->GetTimerManager().SetTimer(WaitReloadTimer, this, &UAttackComponent::OnWaitReloadTimerComplete, 1.985f, false);
	UE_LOG(LogTemp, Log, TEXT("Start Reload"));
}

void UAttackComponent::CompleteReload()
{
	AWeaponBase* Weapon = PlayerCharacter->GetCurrentWeapon();
	int32 MagazineCount = Weapon->WeaponPreset.MagazineCount;

	Weapon->AmmoInven->AddAmmo(Weapon->WeaponPreset.WeaponKind, MagazineCount * 30);
	MagazineCount--;
	UE_LOG(LogTemp, Log, TEXT("MagazineCount : %d"), MagazineCount);

	bReloading = false;

	UE_LOG(LogTemp, Log, TEXT("Completed Reload"));
}

void UAttackComponent::OnWaitReloadTimerComplete()
{
	CompleteReload();
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

bool UAttackComponent::AmmoIsAtMaximum(AWeaponBase* CurrentWeapon)
{
	AAmmoInventory* AmmoInven = CurrentWeapon->AmmoInven;

	int32 CurrentAmmo = AmmoInven->GetAmmo(CurrentWeapon->WeaponPreset.WeaponKind);
	int32 MaxAmmo = AmmoInven->GetMaxAmmo(int32(CurrentWeapon->WeaponPreset.WeaponKind));

	if (CurrentAmmo >= MaxAmmo)
	{
		UE_LOG(LogTemp, Log, TEXT("Current Ammo : %d 이므로 Reload할 필요가 없음"), CurrentAmmo);
		return true;
	}

	return false;
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

