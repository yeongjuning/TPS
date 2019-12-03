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

void UAttackComponent::Attacking()
{
	if (bCanAttack)
	{
		AWeaponBase* Weapon = PlayerCharacter->GetCurrentWeapon();
		if (IsValid(Weapon))
		{
			GetWorld()->GetTimerManager().SetTimer(WaitAttackTimer
				, this, &UAttackComponent::OnWaitAttackTimerEnd
				, 1.0f / PlayerCharacter->GetAttackSpeed(), false);

			StopAttack();
			Weapon->FireAndAttack();
		}
	}
}

void UAttackComponent::Attack()
{
	bCanAttack = true;
	UE_LOG(LogTemp, Log, TEXT("Attack"));
}

void UAttackComponent::StopAttack()
{
	bCanAttack = false;
	UE_LOG(LogTemp, Log, TEXT("Stop Attack"));
}

void UAttackComponent::OnWaitAttackTimerEnd()
{
	Attack();
}

// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ATPSCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

