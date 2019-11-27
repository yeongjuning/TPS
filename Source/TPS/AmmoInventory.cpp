// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoInventory.h"
#include "WeaponBase.h"

AAmmoInventory::AAmmoInventory()
{
	PrimaryActorTick.bCanEverTick = true;
}

int32 AAmmoInventory::GetMaxAmmo()
{
	MaxAmmo.Add(EWeaponKind::Rifle, 30);
	MaxAmmo.Add(EWeaponKind::Knife, 1);
	MaxAmmo.Add(EWeaponKind::Grenade, 3);

	for (TMap<EWeaponKind, int32>::TIterator it = MaxAmmo.CreateIterator(); it; ++it)
	{
		MaxAmmoKey = it->Key;
		MaxAmmoVal = it->Value;
	}

	return MaxAmmoVal;
}

int32 AAmmoInventory::GetTotalAmmoAmount()
{
	TotalAmmoAmount.Add(EWeaponKind::Rifle, 150);
	TotalAmmoAmount.Add(EWeaponKind::Knife, 1);
	TotalAmmoAmount.Add(EWeaponKind::Grenade, 3);

	for (TMap<EWeaponKind, int32>::TIterator it = TotalAmmoAmount.CreateIterator(); it; ++it)
	{
		ToTalAmmoKey = it->Key;
		TotalAmmoAmountVal = it->Value;
	}

	return TotalAmmoAmountVal;
}

int32 AAmmoInventory::GetAmmo(EWeaponKind WeaponKind) const
{
	if (AmmoInventory.Contains(WeaponKind) == false)
		return 0;

	return AmmoInventory[WeaponKind];
}

void AAmmoInventory::AddAmmo(EWeaponKind WeaponKind, int32 AddAmmo)
{
	if (AmmoInventory.Contains(WeaponKind) == false)
		AmmoInventory.Add(WeaponKind, AddAmmo);
	else
		AmmoInventory[WeaponKind] += AddAmmo;
}

int32 AAmmoInventory::ConsumeAmmo(EWeaponKind WeaponKind, int32 MagazineCount)
{
	if (AmmoInventory.Contains(WeaponKind) == false)
	{
		return 0;
	}
	else
	{
		int Ammo = FMath::Min(AmmoInventory[WeaponKind], MagazineCount);
		AmmoInventory[WeaponKind] -= Ammo;
		return Ammo;
	}
}



