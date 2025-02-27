﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoInventory.h"
#include "WeaponBase.h"

AAmmoInventory::AAmmoInventory()
{
	PrimaryActorTick.bCanEverTick = true;
}

int32 AAmmoInventory::GetMaxAmmo(int32 Slot)
{
	switch (Slot)
	{
	case 0:
		MaxAmmo.Add(EWeaponKind::Rifle, 30);
		break;
	case 1:
		MaxAmmo.Add(EWeaponKind::Knife, 1);
		break;
	case 2:
		MaxAmmo.Add(EWeaponKind::Grenade, 3);
		break;
	default:
		break;
	}

	for (TMap<EWeaponKind, int32>::TIterator it = MaxAmmo.CreateIterator(); it; ++it)
	{
		MaxAmmoKey = it->Key;
		MaxAmmoVal = it->Value;
	}

	return MaxAmmoVal;
}

int32 AAmmoInventory::GetTotalAmmoAmount(int32 Slot)
{
	switch (Slot)
	{
	case 0:
		TotalAmmoAmount.Add(EWeaponKind::Rifle, 150);
		break;
	case 1:
		TotalAmmoAmount.Add(EWeaponKind::Knife, 1);
		break;
	case 2:
		TotalAmmoAmount.Add(EWeaponKind::Grenade, 3);
		break;
	default:
		break;
	}
	
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

int32 AAmmoInventory::ConsumeAmmo(EWeaponKind WeaponKind, int32 ConsumeCount)
{
	if (AmmoInventory.Contains(WeaponKind) == false)
		return 0;
	
	if (WeaponKind == EWeaponKind::Knife)
		return 0;
	
	int Ammo = FMath::Min(AmmoInventory[WeaponKind], ConsumeCount);
	AmmoInventory[WeaponKind] -= Ammo;

	return Ammo;
}



